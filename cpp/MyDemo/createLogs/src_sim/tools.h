#pragma once
#include <time.h>
#include <string>
#include <iostream>
#include "singleton.h"

using namespace std;

namespace superman{     //超人命名空间里是我的工具集
    
class MyTime :public Singleton<MyTime>{
public:
    MyTime() {;}
    string GetLocalYMD();//获取系统时间年月日
    string GetLocalYMD(const string &division);//获取系统时间年月日
    string GetLocalHMS();//获取系统时间时分秒
    string GetLocalHMS(const string &division);//获取系统时间时分秒
    long GetCurrentTimestamp();
    string GetLocalTimeYear();
    string GetLocalTimeMonth();
    string GetLocalTimeDay();
    string GetLocalTimeHour();
    string GetLocalTimeMinute();
    string GetLocalTimeSecond();
    void initTime();
private:
    string year,month,day,hour,minute,second;
};



};  //-->superman

