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
#include "Syslog.h"

class ConfigureException : public Error {};

class Conf {
private:
    std::map<std::string, std::string> _configure;
    std::string confPath;
private:
    Conf(const std::string& conPath = "/etc/bug.conf"):confPath(conPath) {load();}

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
            Syslog::log(key + " ---- " + value);
        }
    }

private:
    static Conf *_configureInstance;

public:
    static bool get(const std::string& name, std::string& value) {
        if (_configureInstance == nullptr)
            _configureInstance = new Conf();

        if (_configureInstance->_configure.find(name) == _configureInstance->_configure.end())
            return false;

        value = _configureInstance->_configure[name];
        return true;
    }


    static void reload () {
        _configureInstance->load();
    }
};


#endif //BUG_CONFIGURE_H
