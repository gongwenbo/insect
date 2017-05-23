// © 2016 lenfien

//
// Created by lenfien on 16-10-21.
//

#ifndef BUG_IEPOLLABLE_H
#define BUG_IEPOLLABLE_H

#include <cstdint>
#include <memory>

class IDoable;
class IPollable {
    friend class IDoableFactory;

public:
    virtual ~IPollable() {}

public:
    virtual IDoable* wait_read () = 0;
    virtual IDoable* wait_write () = 0;

    virtual void start(IDoable *doable) = 0;
    virtual void request_read (IDoable *doable) = 0;
    virtual void request_write (IDoable* doable) = 0;
    virtual void stop(IDoable *doable) = 0;
};

#endif //BUG_IEPOLLABLE_H
