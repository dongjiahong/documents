#include <dlfcn.h>		//操作动态库函数的头文件
#include <iostream>
using namespace std;

/*
   参数：
	lib:		动态库*.so的名称
	method:		要调用的方法的名称
*/
void invoke_method(const char *lib, const char *method) {
	void *dl_handle;				//句柄
	void (*func)();					//函数指针
	char *error;

	//1、打开一个共享库对象
	dl_handle = dlopen(lib, RTLD_LAZY);
	if (!dl_handle) {
		cout << "so open filed! error:" << dlerror() << endl;
		return ;
	}

	//2、获取共享库对象在内存里的地址
	func = (void (*)())dlsym(dl_handle, method);
	error = dlerror();
	if (error != NULL) {
		cout << "get method filed! error:" << error << endl;
		return ;
	}

	//3、执行获取的动态库函数
	(*func)();

	//4、关闭动态库
	dlclose(dl_handle);

	return ;
}

/*		动态库函数说明  头文件<dlfcn.h>
	1、	函数原型：void *dlopen(const char *file, int mode);
		函数说明：使对象文件可被程序访问，dlopen函数还会自动解析共享库中的依赖项
				  它有两种模式：
					RTLD_NOW，这表明动态连接器将会在调用dlopen时完成所有必要的在定位
					RTLD_LAZY,这个是在需要时执行在定位
	2、	函数原型：void *dlsym(void *restrict handle, const char*restrict name);
		函数说明：获取执行了dlopen函数的对象文件中的符号的地址，若调用该API时发生了错误，
				  可以使用dlerror函数返回一个表示此错误的人类可读的字符串。
	3、	函数原型：void *dlerror();
		函数说明：返回上一次出现错误的字符串错误
	4、	函数原型：void *dlclose(void *handle);
		函数说明：如果无需在调用共享对象的话，可以调用dlclose来通知操作系统不再需要句柄
				  和对象引用了。
*/
