cmake_minimum_required(VERSION 2.6)
project(Bug)
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(.)

set(SOURCE_FILES
        EpollSys/EPollSystem.h
        EpollSys/IEPollReceiver.h
        OpCenter/OpCenter.h
        Real/Terminal.h
        Runner/DoPoll.cpp
        Runner/DoPoll.h
        Runner/IDoable.h
        Runner/IPollable.h
        Com/Queue.h
        Com/Locker.h
        Com/Syslog.h
        Com/Syslog.cpp
        Com/Error.h
        Database/Database.h
        Database/Database.cpp
        Com/System.h
        Real/PackageListener.h
        Real/PackageProcessor.h
        Real/PackageProcessor.cpp
        Real/Flush.h
        Com/Conf.h
        Com/Conf.cpp
        Phone/Reporter.h
        Phone/Reporter.cpp)

add_executable(Bug Entry/Entry.cpp ${SOURCE_FILES})
add_executable(SimClient UnitTest/SimClient.cpp)

target_link_libraries(Bug pthread mysqlcppconn)
target_link_libraries(SimClient pthread  mysqlcppconn)
