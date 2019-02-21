#include "loadConfig.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>

using namespace std;

//读取配置文件 " adgroup|begin|end|num|flag "
void Config::loadCConfigFromFile() {
    ifstream ifs;
    ifs.open(file_path_.c_str(),ios::in);
    if(!ifs.is_open()) {
        Log::instance().printLogInfo({"Config::loadCConfigFromFile -->文件：",file_path_,"打开失败！"});
        return;
    }
    string str_line;
    while(getline(ifs,str_line)) {
        vector<string> tmpvec;
        boost::split(tmpvec, str_line, boost::is_any_of("|"));
        CCFIG tmpCC;
        tmpCC.platform = tmpvec[0];
        tmpCC.adgroup = boost::lexical_cast<long>( tmpvec[1]);
        tmpCC.beginTime = tmpvec[2];
        tmpCC.endTime = tmpvec[3];
        tmpCC.logNum = boost::lexical_cast<int>( tmpvec[4]);
        tmpCC.logType = tmpvec[5];
        cconfig_vector_.push_back(tmpCC);
        adgroup_vector_.push_back(tmpCC.adgroup);
    }

    ifs.close();
}

void Config::showCConfig() {
    for (const auto &cc : cconfig_vector_) {
        cout << cc.platform << "," <<
            cc.adgroup << "," <<
            cc.beginTime << "," <<
            cc.endTime << "," <<
            cc.logNum << "," <<
            cc.logType << endl;
    }
}
void Config::showAdInfoMap() {  //打印ad_info_map_
    for (map<long,ADINFO>::iterator it= ad_info_map_.begin();it!=ad_info_map_.end();++it) {
        cout << it->first << "," <<
            it->second.adgroup_id << "," <<
            it->second.member_id << "," <<
            it->second.trans_type << "," <<
            it->second.max_price << endl;
    }
}

//通过adgroupid获取数据库里相对于的信息
void Config::getAdgoupInfo(const long& adgroup) {
    string sql = "select adgroup_id,member_id,max_price,trans_type from adgroup where adgroup_id="+boost::lexical_cast<string>(adgroup); 
    ADINFO adinfo;
    size_t row_num=0;
    mysqlpp::StoreQueryResult res;
    res = QueryRunner::instance().query(row_num, sql);
    if (row_num) {
       for(size_t i=0; i<row_num; ++i) {
           adinfo.adgroup_id = res[i]["adgroup_id"];
           adinfo.member_id = res[i]["member_id"];
           adinfo.trans_type = res[i]["trans_type"];
           adinfo.max_price = res[i]["max_price"];
           //...
           ad_info_map_.insert(std::make_pair(adgroup,adinfo));
       } 
    }
}

void Config::configAdInfo() {
    if(!adgroup_vector_.size()) {
        Log::instance().printLogInfo({"Config::configAdInfo() -->配置信息数组未初始化 adgroup_vector_.size()=",boost::lexical_cast<string>(adgroup_vector_.size())});
        return ;
    }
    for (size_t index = 0; index < adgroup_vector_.size(); ++index) {
        getAdgoupInfo(adgroup_vector_[index]);
    }
}


