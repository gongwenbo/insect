// © 2016 lenfien

//
// Created by lenfien on 16-10-21.
//

#ifndef BUG_IEPOLLRECEIVER_H
#define BUG_IEPOLLRECEIVER_H
#include <sys/epoll.h>
#include <exception>

class EPollReceiverError : public std::exception {};

class IEpollReceiver {
    friend class EPollSystem;

protected:
    int _epollfd;

public:
    IEpollReceiver(int epollfd):_epollfd(epollfd) {}
    virtual ~IEpollReceiver() {}

public:
    virtual void notify_new(int) = 0;
    virtual void notify_read(int) = 0;
};

#endif //BUG_IEPOLLRECEIVER_H
