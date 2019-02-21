#pragma once
#include <iostream>
#include "singleton.h"
#include <initializer_list>
#include "tools.h"
using namespace std;
using namespace superman;

class Log : public Singleton<Log> {
public:
    Log():mTime(),log_path_("../log/") {
 //       log_file_ += GetLocalTime();
    }
    void printLogInfo(initializer_list<string> info);
    void setLogFileName();
private:
    MyTime mTime;
    string log_path_;       //log的路径
    string log_file_;
};
