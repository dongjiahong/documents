#pragma once
#include <iostream>
#include <mysql++/mysql++.h>
#include "struct.h"
#include "singleton.h"

using namespace std;

/**
  说明：
	这里是自己使用地三方类mysql++来封装为自己使用的数据库访问工具
 **/

class QueryRunner : public Singleton<QueryRunner>{
public:
	QueryRunner() {;}
	//执行查询语句
    mysqlpp::StoreQueryResult query(size_t &row_num, const string &sql);

	~QueryRunner(){}
    void initQueryRunner(const DBINFO& db_info) {
        this->db_info = db_info;
        conn = mysqlpp::Connection(false);
    }
private:
	DBINFO db_info;
	mysqlpp::Connection conn;
};
