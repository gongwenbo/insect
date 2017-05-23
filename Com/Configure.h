//
// Created by lenfien on 16-11-13.
//

#ifndef BUG_CONFIGURE_H
#define BUG_CONFIGURE_H

#include <iostream>
#include <map>
#include <fstream>
#include <string>

#include "Error.h"
#include "Loger.h"

class ConfigureException : public Error {};

class Configure {
private:
    std::map<std::string, std::string> _configure;
    std::string confPath;
private:
    Configure(const std::string& conPath = "/etc/bug.conf"):confPath(conPath) {load();}

    void load() {
        using namespace std;

        ifstream ifs (confPath);
        if (!ifs)
            throw_exp(ConfigureException, "can not open " + confPath);

        _configure["ftp_path"] = "/home/ftp/";
        _configure["bind_port"] = "8080";
        _configure["max_client"] = "1000";

        string key, value;
        while (ifs >> key >> value) {
            _configure[key] = value;
            Loger::log(key + " ---- " + value);
        }
    }

private:
    static Configure *_configureInstance;

public:
    static bool get(const std::string& name, std::string& value) {
        if (_configureInstance == nullptr)
            _configureInstance = new Configure();

        if (_configureInstance->_configure.find(name) == _configureInstance->_configure.end())
            return false;

        value = _configureInstance->_configure[name];
    }

    static void reload () {
        _configureInstance->load();
    }
};


#endif //BUG_CONFIGURE_H
