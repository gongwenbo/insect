//
// Created by lenfien on 16-10-21.
//

#include "Syslog.h"

pthread_t Syslog::_logThread;
Queue<std::pair<std::string, Syslog::LogType>> Syslog::_msgQue;
bool Syslog::_logStarted = false;
std::ofstream Syslog::_logofs("/var/log/buglog", std::ios_base::app);