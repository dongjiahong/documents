#include "baseFile.h"

//读取文件
bool BaseFile::open_file_read(string &read_cache) {
	cache_vector = "";
    ifs.open(file_path_name.c_str(),ios::in);
    if (!ifs.is_open()) {
        cout << "文件:"<<file_path_name<<"打开失败!" << endl;
        return false;
    }
    string str_line;
    while(getline(ifs,str_line)) {
        cache_vector += str_line;
		cache_vector += "\r\n";
    }
	read_cache = cache_vector;

	ifs.close();
    return true;
}

//写入文件
bool BaseFile::open_file_write(const string &write_cache) {
	cache_vector = "";	
	ofs.open(file_path_name.c_str(),ios::out);
	if (!ofs.is_open()) {
		cout << "文件："<<file_path_name<<"打开失败！"<< endl;
		return false;
	}
	const int str_size = write_cache.size();
	ofs.write(write_cache.c_str(),str_size);

	ofs.close();
    return true;
}

//追加写入文件
bool BaseFile::open_file_app(const string &app_cache) {
	cache_vector = "";
	ofs.open(file_path_name.c_str(),ios::app);
	if (!ofs.is_open()) {
		cout << "文件："<<file_path_name<<"打开失败！"<< endl;
		return false;
	}
	const int str_size = app_cache.size();
	ofs.write(app_cache.c_str(),str_size);

	ofs.close();
    return true;
}
