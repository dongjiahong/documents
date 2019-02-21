#include "tools.h"
#include "struct.h"
#include "QueryRunner.h"
#include "createLog.h"

int main() {
    superman::MyTime::instance().initTime();
    cout << superman::MyTime::instance().GetLocalYMD() << endl;
    cout << superman::MyTime::instance().GetLocalTimeYear() << endl;
    cout << superman::MyTime::instance().GetLocalTimeMonth() << endl;
    cout << superman::MyTime::instance().GetLocalTimeDay() << endl;
    cout << superman::MyTime::instance().GetLocalTimeSecond() << endl;
    DBINFO db{"cpp","localhost","root","dong123"};
    cout <<db.db_name<<db.db_host<<db.db_user<<db.db_paswd<< endl;
    cout << "-----------------" << endl;

    size_t row_num=0;
    string sql = "select * from test";
    QueryRunner::instance().initQueryRunner(db);
    mysqlpp::StoreQueryResult res = QueryRunner::instance().query(row_num,sql);
    if (row_num) {
        for(size_t i=0;i<row_num;++i) {
            cout << res[i]["id"] << "  "<< res[i]["name"] << endl;
        }
    }
    cout << "----------------" << endl;
    cout << CreateLog::instance().getRandom(0,1) << endl;
    cout << CreateLog::instance().getRandom(3,3) << endl;
    cout << CreateLog::instance().getRandom(1,5) << endl;
    return 0;
}
