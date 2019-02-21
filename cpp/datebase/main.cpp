#include "QueryRunner.h"
#include "type.h"

int main(int argc, char *argv[]) {
	DBINFO db_info={
		"test",
		"127.0.0.1",
		"root",
		"dong123"};
	QueryRunner qr(db_info);
	if (qr.query("select * from test;")) {
		mysqlpp::StoreQueryResult res = qr.getQueryResult();
		cout << "res=" << res <<"res.num_rows()="<<res.num_rows()<< endl;
		if (res) {
			for (size_t i=0; i < res.num_rows(); ++i) {
				cout << res[i]["id"] << " "<<
					res[i]["name"] << " "<<
					res[i]["phone"] << endl;
			}
		}
	}
}
