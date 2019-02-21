#include <iostream>
#include <mysql++/mysql++.h>
#include "type.h"
using namespace std;

/**
  说明：
	这里是自己使用地三方类mysql++来封装为自己使用的数据库访问工具
 **/

class QueryRunner{
public:
	QueryRunner(const DBINFO &db_info) {
	//QueryRunner(const string &db_name, const string &mysql_host, const string &user, const string &password) {
		/*
		this->db_name		=	db_name;
		this->mysql_host	=	mysql_host;
		this->user			=	user;
		this->password		=	password;
		//this->res			=	NULL;
		*/
		this->db_info	=	db_info;
		conn = mysqlpp::Connection(false);
	}
	//执行查询语句
	size_t query(const string &sql);

	//获取查询结果
	mysqlpp::StoreQueryResult getQueryResult();

	~QueryRunner(){}
private:
	DBINFO db_info;
	/*
	string db_name;
	string mysql_host;
	string user;
	string password;
	*/
	mysqlpp::Connection conn;
	mysqlpp::StoreQueryResult res;
};
