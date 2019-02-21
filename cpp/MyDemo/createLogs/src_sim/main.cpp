#include "loadConfig.h"
#include "QueryRunner.h"
#include "struct.h"

using namespace std;

int main() {
    DBINFO db_info{"cpp","localhost","root","dong123"};
    //初始化---
    Log::instance().setLogFileName();
    Config::instance().loadCConfigFromFile();
    Config::instance().showCConfig();
    QueryRunner::instance().initQueryRunner(db_info);
    Log::instance().printLogInfo({"1234567"});
    //加载需要造log的信息
    Config::instance().configAdInfo();
    Config::instance().showAdInfoMap();
    //控制log的制造
    
    return 0;
}
