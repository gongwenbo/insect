//
// Created by lenfien on 16-10-21.
//

#include "DoPoll.h"
#include "IDoable.h"

using namespace std;

void *DoPoll::thread_read(void *param) {
    DoPoll& self = *((DoPoll*)param);
    IPollable* ppollable = self._pollable;
    IPollable &poll = *ppollable;

    bool cont;
    IDoable* cdo;
    for (;;) {
        cdo = poll.wait_read();
        cont = cdo->do_read();
        if (!cont)
            cdo->recycle();
        cdo->unlock_read();
    }
    return nullptr;
}

void *DoPoll::thread_write(void *param) {
    DoPoll& self = *((DoPoll*)param);
    IPollable* ppollable = self._pollable;
    IPollable &poll = *ppollable;

    IDoable* cdo;
    bool cont;
    for (;;) {
        cdo = poll.wait_write();
        cont = cdo->do_write();
        if (!cont)
            cdo->recycle();
        cdo->unlock_write();
    }
    return nullptr;
}
