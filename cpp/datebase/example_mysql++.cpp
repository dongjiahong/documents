#include <iostream>
#include <mysql++/mysql++.h>
using namespace std;
/**
	说明：
		这是一个使用第三方库mysql++的简单的小例子。
**/


int main(int argc, char *argv[]) {
	mysqlpp::Connection conn(false);
	//链接数据库 参数：dbName, 服务器地址， 用户名， 密码
	if (conn.connect("test", "127.0.0.1", "root", "dong123")) {
		//执行一个查询
		mysqlpp::Query query = conn.query("select * from test");
		//获取查询结果
		mysqlpp::StoreQueryResult res = query.store();
		if(res) {
			for (size_t i = 0; i < res.num_rows(); ++i) {
				cout << res[i]["id"] << " "
					<< res[i]["name"] << " "
					<< res[i]["phone"] << endl;
			}
		}else {
			cout << "Faild to get data!" << endl;
			exit(EXIT_FAILURE);
		}
	} else {
		cout << "Connect Faild!" << endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}
