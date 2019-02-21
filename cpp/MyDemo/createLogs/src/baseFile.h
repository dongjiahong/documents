#pragma once
#include <iostream>
#include <fstream>  //输入输出文件刘对象

using namespace std;

class BaseFile {
public:
    BaseFile(string file_path_name="") {
        this->file_path_name = file_path_name;   
    }
    bool open_file_read(string &read_cache);   //读一个文件
    bool open_file_write(const string &write_cache); //写一个文件
    bool open_file_app(const string &app_cache);     //追加一个文件
    
    ~BaseFile(){
		ifs.close();
		ofs.close();
		cout << "ifs.close and ofs.close!" << endl;
    }
private:
    
private:
    string file_path_name;
    string cache_vector;    //不管是读还是写都写入在缓存中
    ifstream ifs;
    ofstream ofs;
};


