#include "tools.h"
#include <boost/lexical_cast.hpp>
using namespace std;


void superman::MyTime::initTime() {
    time_t tt = time(NULL);
    struct tm*  current_time_ptr = localtime(&tt);
    char tmp[8];
    strftime(tmp,sizeof(tmp),"%Y",current_time_ptr);
    this->year = string(tmp);
    strftime(tmp,sizeof(tmp),"%m",current_time_ptr);
    this->month = string(tmp);
    strftime(tmp,sizeof(tmp),"%d",current_time_ptr);
    this->day = string(tmp);
    strftime(tmp,sizeof(tmp),"%H",current_time_ptr);
    this->hour = string(tmp);
    strftime(tmp,sizeof(tmp),"%M",current_time_ptr);
    this->minute = string(tmp);
    strftime(tmp,sizeof(tmp),"%S",current_time_ptr);
    this->second = string(tmp);
}

long superman::MyTime::GetCurrentTimestamp() {
    time_t tt =time(NULL);
    return boost::lexical_cast<long>(tt);
}

string superman::MyTime::GetLocalTimeYear() {
    initTime();
    return this->year;
}
string superman::MyTime::GetLocalTimeMonth() {
    initTime();
    return this->month;
}
string superman::MyTime::GetLocalTimeDay() {
    initTime();
    return this->day;
}
string superman::MyTime::GetLocalTimeHour() {
    initTime();
    return this->hour;
}
string superman::MyTime::GetLocalTimeMinute() {
    initTime();
    return this->minute;
}

string superman::MyTime::GetLocalTimeSecond() {
    initTime();
    return this->second;
}

string superman::MyTime::GetLocalYMD() { //获取系统时间,精确到分即可
    initTime();
    string strTime;
    strTime += this->year;
    strTime += this->month;
    strTime += this->day;
    return strTime;
}
string superman::MyTime::GetLocalYMD(const string& division) { //获取系统时间,精确到分即可
    initTime();
    string strTime;
    strTime += this->year;
    strTime += division;
    strTime += this->month;
    strTime += division;
    strTime += this->day;
    return strTime;
}
string superman::MyTime::GetLocalHMS() {
    initTime();
    string strTime;
    strTime += this->hour;
    strTime += this->minute;
    strTime += this->second;
    return strTime;
}
string superman::MyTime::GetLocalHMS(const string& division) {
    initTime();
    string strTime;
    strTime += this->hour;
    strTime += division;
    strTime += this->minute;
    strTime += division;
    strTime += this->second;
    return strTime;
}



