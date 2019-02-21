#include "baseFile.h"
using namespace std;

int main(int argc, char *argv[]) {
    BaseFile bf_r("./log");
    string str;
    bf_r.open_file_read(str);
    cout << str;

	BaseFile bf_w("./log_w");
	string write_str = "11111\r\n22222\r\n33333\r\n";
	bf_w.open_file_write(write_str);

	BaseFile bf_a("./log_w");
	string app_str = "aa\r\nbb\r\ncc\r\n";
	bf_a.open_file_app(app_str);
}
