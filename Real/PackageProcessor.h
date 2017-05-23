//
// Created by lenfien on 16-11-6.
//

#ifndef BUG_PACKAGEPROCESSOR_H
#define BUG_PACKAGEPROCESSOR_H

#include <memory>
#include <vector>
#include "../Com/Queue.h"
#include <sstream>
#include "../Com/Syslog.h"
#include "../Com/System.h"
#include "../Database/Database.h"
#include <fstream>
#include "Flush.h"

class PackageProcessor {
private:
    Queue<std::shared_ptr<std::vector<unsigned char>>> _packageQue;
    Flush _flush;

private:
    PackageProcessor() {
        pthread_t thr;
        pthread_create (&thr, nullptr, _thread_processor, this);
    }

private:
    static void *_thread_processor (void *param) {
        using namespace std;

        PackageProcessor* packageProcessor = reinterpret_cast<PackageProcessor*>(param);

        std::shared_ptr<std::vector<unsigned char>> package;
        istringstream iss;
        ostringstream oss;

        int waterLevel;
        int temperature;
        int windDirection;
        int humunity;

        string location;
        string datetime;
        string uid;
        string picpath;

        int piclen;
        ofstream ofs;

        while (true) {
            package = nullptr;
            packageProcessor->packageProcessor->_packageQue.get(package);
            if (package->size() > 512) {
                std::string header (package->data(), package->data() + 512);
                iss.clear();
                iss.str(header);
                iss >> waterLevel >> temperature >> windDirection >> humunity >> location >> piclen;
                if (iss.fail()) {
                    package = nullptr;
                    Syslog::err("PackageProcessor 执行出错， 因为数据格式不对");
                    continue;
                }

                if (package->size() - 512 != piclen) {
                    Syslog::warning("数据格式错误 piclen和整体长度不匹配");
                    continue;
                }

                System::uid (uid);
                System::now(datetime);
                picpath = uid + ".jpg";

                oss.clear();
                oss.str("");

                oss << "INSERT INTO records (Path, Temperature, Humidity, WaterLevel, WindDir, Location, Time) "
                    << "VALUES ("
                    << "\"" << picpath << "\"" << ", "
                    << humunity << ", "
                    << temperature << ", "
                    << waterLevel << ", "
                    << windDirection << ","
                    << "\"" << location << "\"" << ","
                    << "\"" << datetime  << "\""
                    << ")";

                packageProcessor->_flush.put (picpath, package);
                Database::put (oss.str());
            }
        }
    }

private:

    static PackageProcessor* packageProcessor;

public:
    ///
    static inline void put (std::shared_ptr<std::vector<unsigned char>> pack) {
        if (packageProcessor == nullptr)
            packageProcessor = new PackageProcessor();

        packageProcessor->_packageQue.put(pack);
    }

};

#endif //BUG_PACKAGEPROCESSOR_H
