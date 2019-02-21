#pragma once
#include <iostream>
#include "baseFile.h"

using namespace std;

template<class T>
class Singleton{
public:
static T& instance() {
    //...要保证线程安全的话这里还需要加锁
    if (_instance == NULL){
        _instance = new T;
    }
    return *_instance;
}
protected:
    Singleton<T>(){;}       //构造
    
    class Garbo{    //Garbo是垃圾清洁工的意思
    public:
        ~Garbo(){
            if (Singleton<T>::_instance) {
                delete Singleton<T>::_instance;
                cout << "delete Singleton" << endl;
                _instance = NULL;
            }
        }
    };
    
static Garbo garbo;
static T* _instance;
};

template<class T> 
T* Singleton<T>::_instance = NULL;
