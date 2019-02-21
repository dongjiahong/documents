#include "singleton.h"
#include "singletonB.h"
#include "singletonC.h"
#include "../file/baseFile.h"

/*
   自己区分singleton和singletonB的区别，
   singleton能继承，singletonB不能继承
   这是因为singleton的构造函数是私有。
   */
class Test : public Singleton<Test> {
public:
    Test() {cout << "Test" << endl;}
	void play() {cout << "play!" << endl;}
    virtual ~Test(){cout << "~Test" << endl;}
};


class TestB  {
public:
	void play() {cout << "playB" << endl;}
};

class TestC : public SingletonC<TestC> {
public: 
    void play() {cout << "playC" << endl;}
};

class A {
public:
    A(){cout << "A()" << endl;}
    ~A(){cout << "~A()" << endl;}
};

class B : public A{
public:
    B(){cout << "B()" << endl;}
    ~B(){cout << "~B()" << endl;}
};

int main(int argc, char *argv[]) {
	//
//	typedef SingletonB<TestB> TestB;
//	TestB::instance().play();

    {
	    Test::instance().play();	
    }
    B b;

    TestC::instance().play();
    BaseFile fi("./loggg");
    //string str = "xxxxx";
    //fi.open_file_write(str);
    fi.open_file_write("YYYY");
	//Test t;
	//t.play();
	return 0;
}
