#pragma once
#include <iostream>
#include "../file/baseFile.h"

using namespace std;

template<class T>
class SingletonC{
public:
static T& instance() {
    //...要保证线程安全的话这里还需要加锁
    if (_instance == NULL){
        _instance = new T;
    }
    return *_instance;
}
protected:
    SingletonC<T>(){;}       //构造
    
    class Garbo{    //Garbo是垃圾清洁工的意思
    public:
        ~Garbo(){
            if (SingletonC<T>::_instance) {
                delete SingletonC<T>::_instance;
                cout << "delete SingletonC" << endl;
                _instance = NULL;
            }
        }
    };
    
static Garbo garbo;
static T* _instance;
};

template<class T> 
T* SingletonC<T>::_instance = NULL;
