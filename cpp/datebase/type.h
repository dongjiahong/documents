#pragma once
#include <iostream>
using namespace std;

//定义结构体用来存放数据库信息
typedef struct db_info_machine{
	string db_name;
	string db_host;
	string db_user;
	string db_paswd;
}DBINFO;
