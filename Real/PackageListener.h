//
// Created by lenfien on 16-11-6.
//

#ifndef BUG_DATAPROCESSOR_H
#define BUG_DATAPROCESSOR_H

#include <vector>
#include <memory>
#include <deque>
#include "../Com/Syslog.h"

class PackageListener {
private:
    bool _error = false;
    std::deque<std::shared_ptr<std::vector<unsigned char>>> _readys;
    std::shared_ptr<std::vector<unsigned char>> _data = nullptr;

public:
    enum Stat { WBEG = 0, WEND = 1, WNEXT0XCC = 2 };

private:
    Stat _stat = WBEG;

public:
    PackageListener()   {}
    virtual ~PackageListener()  {}

public:
    bool put (std::vector<unsigned char>::iterator beg, std::vector<unsigned char>::iterator end) {
        for (auto it = beg; it < end; ++it) {
            if (_stat == WBEG) {
                if (*it == 0xaa) {
                    _stat = Stat::WEND;
                    _data = std::make_shared<std::vector<unsigned char>>();
                    continue;
                }
            }
            else if (_stat == WEND) {
                if (*it == 0xcc) {
                    it += 1;
                    if (it == end) {
                        _stat = WNEXT0XCC;
                        continue;
                    }

                    if (*it != 0xaa && *it != 0xbb && *it != 0xcc) {
                        Syslog::err("Next to 0xcc is not 0xaa 0xbb 0xcc");
                        _error = true;
                        _data = nullptr;
                        _stat = WBEG;
                    }
                }
                else {
                    if (*it == 0xbb) {
                        _stat = WBEG;
                        _readys.push_back (_data);
                        _data = nullptr;
                        continue;
                    }
                }

                if (_data != nullptr)
                    _data->push_back (*it);
            }
            else if (_stat == WNEXT0XCC) {
                if (*it != 0xaa && *it != 0xbb && *it != 0xcc) {
                    Syslog::err("Next to 0xcc is not 0xaa 0xbb 0xcc");
                    _error = true;
                    _data = nullptr;
                    _stat = WBEG;
                }

                _stat = WEND;
                if (_data != nullptr)
                    _data->push_back (*it);
            }
        }

        return _readys.size() > 0;
    }

    std::shared_ptr<std::vector<unsigned char>>
    encode (std::vector<unsigned char>::iterator beg,
            std::vector<unsigned char>::iterator end) {
        std::shared_ptr<std::vector<unsigned char>> pack = std::make_shared<std::vector<unsigned char>>();
        pack->push_back(0xaa);
        for (auto v = beg; v != end; ++v) {
            if (*v == 0xaa || *v == 0xbb)
                pack->push_back(0xcc);
            pack->push_back(*v);
        }
        pack->push_back(0xbb);
        return pack;
    }

    std::shared_ptr<std::vector<unsigned char>> get() {
        if (_readys.size() == 0)
            return nullptr;
        auto res = _readys.front();
        _readys.pop_front();
        return res;
    }

    bool error() {
        return _error;
    }

    void clear() {
        _error = false;
        _readys.clear();
        _stat = Stat::WBEG;
    }
};

#endif //BUG_DATAPROCESSOR_H
