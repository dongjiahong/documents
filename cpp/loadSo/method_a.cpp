#include <iostream>

using namespace std;

//加 extern "C" 标识，是因为gcc编译器编辑c文件的函数名不会变，
//不加的话也不知道pritHello这个名称在编译后会变成什么
extern "C" void printHello() {
	cout << "Hello, I'm A!!" << endl;
}
