#pragma once

#include <iostream>

using namespace std;

/*
   这里是实现了单例模式的但线程版，这里不保证线程安全
   如果需要线程安全，请使用锁
   */

template<class T> class Singleton {
public:
	static T& instance() {
		if (!__instance) {
			__instance = new T;
		}
		return *__instance;
	}
protected:
	Singleton(){;}
	virtual ~Singleton() {
		cout << "Singleton::~Singleton" << endl;

		return;
		//delete _instance
		if (__instance) {
			T* t = __instance;
			__instance = NULL;
			delete t;
		}
        cout << "delete singleton complate!" << endl;
	}

	Singleton(const Singleton& rhs);
	Singleton& operator=(const Singleton& rhs);

protected:
	static T* __instance;
};
//静态变量在外面初始化
template<class T> T* Singleton<T>::__instance = 0;
