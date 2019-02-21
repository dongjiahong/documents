#pragma once
#include <map>
#include <set>
#include "struct.h"
#include "singleton.h"

using namespace std;

class CreateLog :public Singleton<CreateLog > {
public:
    void createPv(const CCFIG &cc, const string &division);
    void createSnd(const CCFIG &cc, const string &division);
    void createClick(const CCFIG &cc, const string &division);
    string getRandom(const int &small,const int &digit);
private: 
    string getBid(const string& platfrom);
    //存放bid,{platform:{"1234","1235","234"..}}
    map<string, set<string> > platform_bid_map_;
};
