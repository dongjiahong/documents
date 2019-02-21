#pragma once

#include <iostream>
#include <vector>
#include <map>
#include "singleton.h"
#include "struct.h"
#include "log.h"
#include "QueryRunner.h"


using namespace std;

class Config : public Singleton<Config> {
public:
    Config():file_path_("../etc/conf"),division_flag_("|"){}
    void loadCConfigFromFile();
    void configAdInfo();
    void showCConfig();
    void showAdInfoMap();
private:
    void getAdgoupInfo(const long& adgroup);
private:
    vector<long> adgroup_vector_;   //要造log的广告
    vector<CCFIG> cconfig_vector_; //配置信息的数组
    map<long, ADINFO > ad_info_map_;  //有效广告的信息
    string file_path_;      //要加载文件的路径
    string division_flag_;  //加载文件的分隔符

};
//加载配置信息从文件
//加载配置信息从数据库
