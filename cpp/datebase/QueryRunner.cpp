#include "QueryRunner.h"

//输入sql语句，获取查询结果
size_t QueryRunner::query(const string &sql) {
	size_t row_num = 0;
	try{
		//建立链接
		if (conn.connect(db_info.db_name.c_str(), db_info.db_host.c_str(), db_info.db_user.c_str(), db_info.db_paswd.c_str())) {
			//建立查询
			mysqlpp::Query query = conn.query(sql);
			//获取查询结果
			mysqlpp::StoreQueryResult res = query.store();
			//保存查询结果
			this->res = res;
			row_num = res.num_rows();
		}
	} catch (const mysqlpp::Exception &e) {
        cout << "查询失败：" << e.what() << endl;
	} catch (...) {
		cout << "查询失败！"<< endl;
	}

	return row_num;
}

//获取查询结果
mysqlpp::StoreQueryResult QueryRunner::getQueryResult() {
	if (this->res){
		return this->res;
	}
}
