//
// Created by lenfien on 16-10-21.
//

#ifndef BUG_EPOLLRUNNER_H
#define BUG_EPOLLRUNNER_H

#include <memory>
#include <vector>
#include <pthread.h>

#include "../Runner/IPollable.h"
#include "../Com/Syslog.h"
#include <cstring>
#include <signal.h>

class DoPollException : public Error {};

class DoPoll {
private:
    static void *thread_read (void *param);
    static void *thread_write (void *param);

public:
    DoPoll(IPollable* ipollable):_pollable(ipollable) {
        pthread_t thr;
        int err;
        for (int i = 0; i < 50; ++i) {
            err = pthread_create (&thr, nullptr, thread_read, this);
            if (err != 0)
                throw_exp(DoPollException, "pthread_create failed");
            _readThreads.push_back(thr);
        }

        for (int i = 0; i < 50; ++i) {
            err = pthread_create (&thr, nullptr, thread_write, this);
            if (err != 0)
                throw_exp(DoPollException, "pthread_create failed");
            _writeThreads.push_back(thr);
        }

        Syslog::log("DoPoll Init OK");
    }

private:
    IPollable* _pollable;
    std::vector<pthread_t> _readThreads;
    std::vector<pthread_t> _writeThreads;
};


#endif //BUG_EPOLLRUNNER_H
