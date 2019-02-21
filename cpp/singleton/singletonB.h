#pragma once

template <class T>
class SingletonB {
public:
	static T& instance() {
		static T _instance;
		return _instance;
	}
private:
	SingletonB(){;}
	~SingletonB(){;}
	SingletonB(SingletonB const&);
	SingletonB& operator=(SingletonB const&);
};
