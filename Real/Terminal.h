//
// Created by lenfien on 16-10-21.
//

#ifndef BUG_TERMINAL_H
#define BUG_TERMINAL_H

#include "../Com/Syslog.h"
#include <sys/socket.h>
#include "../Runner/IPollable.h"
#include <fstream>
#include <sstream>
#include "../Com/System.h"
#include "../Database/Database.h"
#include "PackageProcessor.h"
#include "PackageListener.h"

class Terminal : public IDoable {
private:
    std::vector<unsigned char> _readBuffer;
    ssize_t         _readCount = 0;
    size_t          _bytes = 0;
    Queue<std::string>  _sendQueue;
    PackageListener     _packageListener;

public:
    Terminal (IPollable* pollable): IDoable(pollable), _readBuffer(1024) {}
    virtual ~Terminal() {}

    virtual bool do_read() override {
        using namespace std;

        bool contin = true;
        ssize_t rn;

        if (_readCount ++ == 0)
            return true;

        errno = 0;
        while ((rn = recv (_fd, _readBuffer.data(), _readBuffer.size(), MSG_DONTWAIT)) > 0) {
            _bytes += rn;
            Syslog::log("Bytes : " + to_string(_bytes));
            _packageListener.put(_readBuffer.begin(), _readBuffer.begin() + rn);
            if (_packageListener.error()) {
                contin = false;
                break;
            }

            for (auto v = _packageListener.get(); v != nullptr; v = _packageListener.get()) {
                PackageProcessor::put(v);
                Syslog::log("新包被加入");
                _sendQueue.put("RECEIVED OK\r\n");
                request_write();
            }
        }

        if (rn == 0 || (errno != 0 && errno != EAGAIN))
            contin = false;

        errno = 0;
        return contin;
    }

    virtual bool do_write() override {
        using namespace std;
        string msg;
        if (_sendQueue.try_pop(msg))
            send (get_fd(), msg.data(), msg.size(), MSG_WAITALL);
        return true;
    }

    virtual void reset() override {
        _readCount = 0;
        _bytes = 0;
        _packageListener.clear();
    }
};

class TerminalFactory :public IDoableFactory {
public:
    virtual IDoable* make_doable(IPollable* poll) override {
        return new Terminal(poll);
    }
};




#endif //BUG_TERMINAL_H
