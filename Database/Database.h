//
// Created by lenfien on 16-11-5.
//

#ifndef BUG_DB_H
#define BUG_DB_H

#include "../Com/Locker.h"
#include "../Com/Queue.h"

#include <memory>
#include <vector>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "../Com/Syslog.h"

class DatabaseError : public Error {};

class Database {
private:
    Queue<std::string> _sqlQueue;
    std::vector<pthread_t> _threads;

    sql::Driver *_driver;
    std::string _host, _usr, _pass;

    pthread_t _loadReport;

private:
    Database (const std::string& host, const std::string& usr, const std::string& pass):
            _host(host), _usr(usr), _pass(pass) {

        _driver = get_driver_instance();
        if (_driver == nullptr)
            throw_exp(DatabaseError, "get_driver_instance returns null!");

        for (int i = 0; i < 4; ++i) {
            pthread_t thr;
            pthread_create (&thr, nullptr, _thr_database, this);
            pthread_detach(thr);
            _threads.push_back(thr);
        }

        pthread_create (&_loadReport, nullptr, _thr_load_report, this);
    }

    static void *_thr_database (void *param) {
        using namespace std;

        Database *db = reinterpret_cast<Database *>(param);
        string sql;

        bool _needConnection = true;
        shared_ptr<sql::Connection> _connection = nullptr;
        shared_ptr<sql::Statement> _statment = nullptr;

        while (true) {
            if (_needConnection) {
                try {
                    _connection.reset(db->_driver->connect(db->_host, db->_usr, db->_pass));
                    _statment.reset(_connection->createStatement());
                    _statment->execute("USE bug");
                    _needConnection = false;
                }
                catch (sql::SQLException& ex) {
                    Syslog::log("Connecting to mysql failed");
                    usleep (1000000);
                    continue;
                }
            }

            db->_sqlQueue.get(sql);

            try {
                _statment->execute(sql);
                errno = 0;
            }
            catch (sql::SQLException& ex) {
                Syslog::err(string("mysql execute failed:") + ex.what());
                Syslog::err("Mysql errcode : " + to_string(ex.getErrorCode()));
                if (ex.getErrorCode() == 2013) {
                    _statment = nullptr;
                    db->_sqlQueue.put(sql);
                    _needConnection = true;
                }
                else {
                    Syslog::fatal("Mysql crushed!!!");
                    return nullptr;
                }
            }
        }
    }

    static void *_thr_load_report(void *param) {
        Database * pdatabase = (Database*)param;
        Database &db = *pdatabase;
        size_t preLoad = 0;

        while (1) {
            usleep (1000);
            if (preLoad != db._sqlQueue.count()) {
                preLoad =  db._sqlQueue.count();
                Syslog::log("Mysql load : " + std::to_string(preLoad));
            }
        }
    }

public:
    static Database* _db;
    static void put (const std::string& sql) {
        if (_db == nullptr)
            _db = new Database("localhost", "bugdatabase", "letitgo");

        if (_db != nullptr)
            _db->_sqlQueue.put(sql);
    }
};




#endif //BUG_DB_H
