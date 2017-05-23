//
// Created by lenfien on 16-10-21.
//

#ifndef BUG_EPOLL_H
#define BUG_EPOLL_H

#include <memory>
#include <stdexcept>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <assert.h>

#include "../Com/Syslog.h"
#include "../EpollSys/IEPollReceiver.h"
#include <bits/sigthread.h>
#include "../Com/Error.h"
#include <fcntl.h>
#include <netdb.h>

class EPollSystermError : public Error {};

class EPollSystem {
public:
    EPollSystem(int epollfd, IEpollReceiver* receiver)
            :_epollReceiver(receiver),
             _epollfd(epollfd),
             _bsock(socket (AF_INET, SOCK_STREAM, 0)) {

        // Adress reusable configuration
        {
            int v = 1, l = sizeof (v);
            ::setsockopt (_bsock, SOL_SOCKET, SO_REUSEADDR, &v, (socklen_t) l);
        }

        // non block accept
        {
            int flag, err;
            err = fcntl(_bsock, F_GETFL, &flag);
            assert (err != -1);
            err = fcntl(_bsock, F_SETFL, flag & O_NONBLOCK);
            assert (err != -1);
        }

        {
            Conf::get("bind_port", _bindPort);

            addrinfo *result, hint;
            memset(&hint, 0, sizeof (hint));
            hint.ai_family = AF_INET;
            hint.ai_protocol = IPPROTO_TCP;
            hint.ai_flags = AI_PASSIVE;
            hint.ai_socktype = SOCK_STREAM;

            getaddrinfo (nullptr, _bindPort.c_str(), &hint, &result);

            if (-1 == ::bind (_bsock, result->ai_addr, result->ai_addrlen)) {
                ::close (_bsock);
                ::close (_epollfd);
                throw_exp (EPollSystermError, "");
            }
            ::listen(_bsock, 120);
        }

        /* Bind socket to port and listen */
        {
            epoll_event event;
            memset (&event, 0, sizeof(event));
            event.data.fd = _bsock;
            event.events = EPOLLIN;
            if (-1 == ::epoll_ctl (_epollfd, EPOLL_CTL_ADD, _bsock, &event)) {
                ::close (_bsock);
                ::close (_epollfd);
                throw_exp (EPollSystermError, "");
            }
        }

        /* Create a thread */
        if (::pthread_create (&_thrMain, nullptr, epoll_main_thread, this) != 0) {
            ::close (_bsock);
            ::close (_epollfd);
            throw_exp (EPollSystermError, "");
        }

        Syslog::log("EPollSystem reset OK.");
    }

    /*
     * EPollSystem can not be copied
     */
    EPollSystem (const EPollSystem& ) = delete;
    EPollSystem (EPollSystem&& other) = delete;

    /*
     * Must cancel thread before destroyed anything with this thread.
     */
    virtual ~EPollSystem() {
        if (::pthread_cancel (_thrMain) == 0)
            ::pthread_join (_thrMain, nullptr);
        ::close (_epollfd);
    }

    /*
     * Move operator =
     */
    EPollSystem& operator = (EPollSystem&& other) = delete;
    EPollSystem& operator = (const EPollSystem& other) = delete;

private:
    epoll_event _revents[128];

private:
    static void *epoll_main_thread(void *param) {
        using namespace std;

        EPollSystem* pself = reinterpret_cast<EPollSystem*> (param);
        IEpollReceiver* receiver = pself->_epollReceiver;
        int epfd = pself->_epollfd;
        int bsock = pself->_bsock;

        epoll_event *revents = pself->_revents;
        int reventsn = sizeof (pself->_revents) / sizeof(revents[0]);

        int cfd;            // current file fd
        uint32_t cevents;   //current events
        int newfd;          //new client connected
        int repoll;
        for (;;) {
            repoll = epoll_wait (epfd, revents, reventsn, -1);
            if (repoll == -1 && errno == EINTR)
                continue;

            if (repoll == -1) {
                Syslog::err("epoll_wait");
                break;
            }

            for (int i = 0; i < repoll; ++i) {
                cfd = revents[i].data.fd;
                cevents = revents[i].events;

                if (cevents & EPOLLIN) {
                    if (bsock == cfd) {
                        newfd = accept (bsock, nullptr, nullptr);
                        if (newfd != -1)
                            receiver->notify_new(newfd);
                        else
                            Syslog::err("Accept failed");
                    }
                    else
                        receiver->notify_read(pself->_revents[i].data.fd);
                }
            }
        }
        return nullptr;
    }

private:
    IEpollReceiver* _epollReceiver;
    int             _epollfd;
    int             _bsock;
    pthread_t       _thrMain;
    std::string     _bindPort;
};


#endif //BUG_EPOLL_H
