//
// Created by lenfien on 16-10-21.
//

#ifndef BUG_EPOLLCENTER_H
#define BUG_EPOLLCENTER_H

#include <memory>
#include <vector>
#include <stdint.h>
#include <cstring>
#include <tuple>
#include <unistd.h>
#include <netinet/tcp.h>
#include <atomic>
#include "../Com/Conf.h"
#include "../Runner/IDoable.h"
#include "../Com/Queue.h"
#include "../Com/Syslog.h"
#include "../EpollSys/IEPollReceiver.h"
#include "../Runner/IPollable.h"

class DataCenterError : public Error {};
class OpCenter : public IEpollReceiver, public IPollable {
private:
    IDoableFactory* _doableFactory;

    std::vector<IDoable*> _doables;    //fd -> doable, sid
    std::vector<uint64_t> _sessionIdMap;    // fd -> sessionId

    Rwlocker _rwl_sessionIdMap;
    uint64_t _sessionId = 1;

    Queue<std::tuple<IDoable*, uint64_t>> _readQueue;    // IDoable*, sessionId
    Queue<std::tuple<IDoable*, uint64_t>> _writeQueue;   // IDoable*, sessionId
    Queue<std::tuple<IDoable*, uint64_t>> _recycleQueue;                  // 回收队列

    std::atomic<uint64_t > _counter;

public:
    OpCenter (int epfd, IDoableFactory* factory):
           IEpollReceiver(epfd), _doableFactory(factory) {
        std::string strMaxClient;
        Conf::get("max_client", strMaxClient);
        int maxClient = std::stoi(strMaxClient);
        for (int i = 0; i < maxClient; ++i)
            _doables.push_back(_doableFactory->make_doable(this));
        _sessionIdMap.resize ((unsigned long) maxClient);

        _counter = 0;
        pthread_t recycleThread;
        pthread_create (&recycleThread, nullptr, _recycle_thread, this);
    }

    virtual ~OpCenter() override {}

public:
    /******** Invoked by EPollSystem Begin ***************/
    virtual void notify_new (int fd) override {
        using namespace std;

        if (fd >= static_cast<int>(_doables.size())) {
            Syslog::log ("REJECT client connection");
            close (fd);
            return ;
        }

        if (_doables[fd]->is_alive())
            throw_exp(DataCenterError, "specifing an fd to an alived fd slot");

        // reinit session ID
        {
            AutoRlocker rlocker (_rwl_sessionIdMap);
            _sessionIdMap[fd] = _sessionId;
        }

        _doables[fd]->make_live(fd, _sessionId);
        start(_doables[fd]);
        _sessionId ++;

        _counter += 1;

        Syslog::log("NEW " + to_string(_counter));
        _readQueue.put(std::make_tuple(_doables[fd], _sessionIdMap[fd]));
        _writeQueue.put(std::make_tuple(_doables[fd], _sessionIdMap[fd]));
    }

    virtual void notify_read(int fd) override {
        AutoRlocker rlocker (_rwl_sessionIdMap);
        _readQueue.put(std::make_tuple(_doables[fd], _sessionIdMap[fd]));
    }
    /******** Invoked by EPollSystem End ***************/

public:
    virtual IDoable* wait_read() override {
        using namespace std;
        uint64_t sid;

        tuple<IDoable*, uint64_t> msg;
        IDoable* doable;

        while (true) {
            _readQueue.get(msg);
            tie(doable, sid) = msg;

            if (!doable->is_doable())    // 如果已经doable已经死亡，就没必须再执行了
                continue;

            /* 如果是上一个会话残留下的执行请求则丢弃 */
            {
                AutoRlocker rlock (_rwl_sessionIdMap);
                if (sid != _sessionIdMap[doable->get_fd()])
                    continue;
            }

            if (doable->try_lock_read())
                return doable;
            else
                _readQueue.put(msg);
        }
    }
    virtual IDoable* wait_write() override {
        using namespace std;
        uint64_t sid;

        tuple<IDoable*, uint64_t> msg;
        IDoable* doable;
        while (true) {
            _writeQueue.get(msg);
            tie(doable, sid) = msg;

            if (!doable->is_doable())    // 如果已经doable已经死亡，就没必须再执行了
                continue;

            /* 如果是上一个会话残留下的执行请求则丢弃 */
            {
                AutoRlocker rlock (_rwl_sessionIdMap);
                if (sid != _sessionIdMap[doable->get_fd()])
                    continue;
            }

            if (doable->try_lock_write())
                return doable;
            else
                _writeQueue.put(msg);
        }
    }

    virtual void start(IDoable *doable) override {
        epoll_event ev;
        ev.data.fd = doable->get_fd();
        ev.events = EPOLLIN | EPOLLET;
        epoll_ctl (_epollfd, EPOLL_CTL_ADD, doable->get_fd(), &ev);
    }
    virtual void stop(IDoable *doable) override {
        epoll_ctl (_epollfd, EPOLL_CTL_DEL, doable->get_fd(), nullptr);
        _recycleQueue.put(std::make_tuple(doable, doable->get_sid()));
    }

    virtual void request_write(IDoable *doable) override {
        _writeQueue.put(std::make_tuple(doable, doable->get_sid()));
    }
    virtual void request_read(IDoable *doable) override {
        _readQueue.put(std::make_tuple(doable, doable->get_sid()));
    }

public:
    bool is_in_session(IDoable *doable, uint64_t sid) {
        AutoRlocker rlocker(_rwl_sessionIdMap);
        return sid == _sessionIdMap[doable->get_fd()];
    }

private:
    static void *_recycle_thread(void *param) {
        using namespace std;
        OpCenter* opCenter = reinterpret_cast<OpCenter*>(param);

        IDoable* doable;
        uint64_t sid;
        tuple<IDoable*, uint64_t> msg;
        bool ok;
        while (true) {
            opCenter->_recycleQueue.get(msg);
            tie(doable, sid) = msg;
            if (doable->can_be_recycled() && opCenter->is_in_session(doable, sid)) {
                if (doable->try_lock_read()) {
                    if (doable->try_lock_write()) {
                        doable->make_die();
                        opCenter->_counter -= 1;
                        ok = true;
                        Syslog::log("Recycled " + to_string(opCenter->_counter));
                    }
                    else {
                        doable->unlock_read();
                        ok = false;
                    }
                }
                else
                    ok = false;

                if (!ok)
                    opCenter->_recycleQueue.put(msg);
            }
        }
    }
};


#endif //BUG_EPOLLCENTER_H
