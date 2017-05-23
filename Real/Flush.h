//
// Created by lenfien on 16-11-10.
//

#ifndef BUG_FLUSH_H
#define BUG_FLUSH_H

#include <vector>
#include <memory>
#include <unistd.h>
#include "../Com/Queue.h"
#include <thread>
#include "../Com/Syslog.h"
#include <fstream>
#include "../Com/Conf.h"
#include <sys/stat.h>

class FlushException : public Error {};

class Flush {
private:
    Queue<std::pair<std::string, std::shared_ptr<std::vector<unsigned char>>>> _queue;
    std::vector<pthread_t> _flushThreads;
    pthread_t _thrLoadReport;

    std::string _ftp_path = "ftp";

public:
    Flush () {
        Conf::get("ftp_path", _ftp_path);
        mkdir(_ftp_path.c_str(), 0777);

        pthread_t _thrFlush;
        for (int i = 0; i < 5; ++i) {
            int err = pthread_create (&_thrFlush, nullptr, _flush_thread, this);
            if (err != 0)
                throw_exp(FlushException, "Flush thread create failed");
            _flushThreads.push_back(_thrFlush);
        }

        pthread_create (&_thrLoadReport, nullptr, _thr_load_report, this);
    }

    ~Flush () {
        for (pthread_t thr : _flushThreads) {
            pthread_cancel (thr);
            pthread_join(thr, nullptr);
        }
    }

    void put (const std::string& path,
              std::shared_ptr<std::vector<unsigned char>> pack) {
        _queue.put (std::make_pair(path, pack));
    }

private:
    static void *_flush_thread (void *param) {
        using namespace std;

        Flush *pflush = reinterpret_cast<Flush*>(param);
        Flush& flu = *pflush;
        pair<string, shared_ptr<std::vector<unsigned char>>> pack;

        while (true) {
            flu._queue.get(pack);
            ofstream ofs(flu._ftp_path + "/" + pack.first);
            if (!ofs) {
                Syslog::warning(pack.first + " create failed");
                continue;
            }

            ofs.write ((const char *) (pack.second->data() + 512), pack.second->size() - 512);
            ofs.close ();

            Syslog::log(pack.first + " 已经被存储到ftp");
            pack.second.reset();
        }
    }

    static void *_thr_load_report(void *param) {
        Flush *pflush = (Flush*)param;
        Flush &flush = *pflush;
        size_t preLoad = 0;

        while (1) {
            usleep (10000);
            if (preLoad != flush._queue.count()) {
                preLoad =  flush._queue.count();
                Syslog::log("Flush load : " + std::to_string(preLoad));
            }
        }
    }
};


#endif //BUG_FLUSH_H
