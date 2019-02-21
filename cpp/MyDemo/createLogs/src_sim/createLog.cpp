#include "createLog.h"
#include <time.h>
#include <boost/lexical_cast.hpp>
#include "struct.h"

using namespace std;

string CreateLog::getRandom(const int &small, const int &digit) {
    //返回一个>=small 的digit位数
    if(digit == 0) {
        return "wrong";
    }
    string res;
    srand((unsigned)time(NULL)); //时间戳当随机数种子
    int rd = rand()%10;
    rd+=small;
    res += boost::lexical_cast<string>(rd);
    for(int i=1; i<digit; ++i) {
        rd = rand()%10;
        res += boost::lexical_cast<string>(rd);
    }
    return res;
}

string CreateLog::getBid(const string &platform) {
    string res = "wrong";
    if (platform == "mz") {
    } else if(platform == "ky") {
    } else if(platform == "bd") {
    } else if(platform == "tb") {
    } else if(platform == "mg") {
    }
    return res;
}

void CreateLog::createPv(const CCFIG &cc, const string &divsion="|") {
    string bid = getBid(cc.platform);
}

void CreateLog::createSnd(const CCFIG &cc, const string &divsion="|") {

}

void CreateLog::createClick(const CCFIG &cc, const string &divsion="|") {

}

