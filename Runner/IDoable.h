//
// Created by lenfien on 16-10-23.
//

#ifndef BUG_IDOABLE_H
#define BUG_IDOABLE_H

#include <memory>
#include <unistd.h>

#include "../Com/Syslog.h"
#include <sys/epoll.h>
#include "../Runner/IPollable.h"

class IDoableError : public Error {};
class IDoable {
    friend class IPollable;

protected:
    uint64_t    _sid;
    int         _fd;
    IPollable*  _pollable;

private:
    Mutex   _mtx_update;
    bool    _isRLocked = false;
    bool    _isWLocked = false;

    bool    _isAlive = false;
    bool    _isRecycling = false;

public:
    IDoable(IPollable* poll):_pollable(poll) {}
    virtual ~IDoable() {}

public:
    inline uint64_t get_sid() {return _sid;}    // get sid
    inline int get_fd() {return _fd;}           // get fd

public:
    /************* Invoked by poller Begin ************/
    inline bool try_lock_read() {
        Autolock<Mutex> locker (_mtx_update);
        if (!_isRLocked) {
            _isRLocked = true;
            return true;
        }
        return false;
    }
    inline void unlock_read() {
        Autolock<Mutex> locker (_mtx_update);
        _isRLocked = false;
    }

    inline bool try_lock_write() {
        Autolock<Mutex> locker (_mtx_update);
        if (!_isWLocked) {
            _isWLocked = true;
            return true;
        }
        return false;
    }
    inline void unlock_write() {
        Autolock<Mutex> locker (_mtx_update);
        _isWLocked = false;
    }

    void make_live(int fd, uint64_t sid) {
        Autolock<Mutex> locker (_mtx_update);
        _fd = fd;
        _sid = sid;
        _isRLocked = false;
        _isWLocked = false;
        _isRecycling = false;
        _isAlive = true;
    }

    void make_die() {
        Autolock<Mutex> locker (_mtx_update);
        _isRLocked = false;
        _isWLocked = false;
        _isAlive = false;
        _isRecycling = false;
        reset();    // Init child
        ::close (_fd);
    }

    inline bool is_alive () {
        Autolock<Mutex> locker (_mtx_update);
        return _isAlive;
    }
    inline bool is_doable() {
        Autolock<Mutex> locker (_mtx_update);
        return _isAlive && !_isRecycling;
    }
    inline bool can_be_recycled() {
        Autolock<Mutex> locker (_mtx_update);
        return _isAlive && _isRecycling;
    }
    /************* Invoked by poller End *************/

public:
    /************ Invoked by child Begin **********/
    inline void recycle () {
        Autolock<Mutex> locker (_mtx_update);
        if (!_isRecycling) {
            _isRecycling = true;
            _pollable->stop(this);
        }
    }

    inline void request_write () {
        _pollable->request_write(this);
    }

    inline void request_read () {
        _pollable->start(this);
    }
    /************ Invoked by child End **********/

public:
    /************ Implement by child Begin **********/
    virtual bool do_read () = 0;
    virtual bool do_write () = 0;
    virtual void reset() = 0;
    /************ Implement by child End ************/
};

class IDoableFactory {
public:
    virtual IDoable* make_doable(IPollable* poll) = 0;
};

#endif //BUG_IDOABLE_H
