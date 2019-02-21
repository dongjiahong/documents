#ifndef __BLOOM_H__
#define __BLOOM_H__

#include <vector>
#include "hashfun.h"

using namespace std;

class Bloom {
public:
	Bloom(const int &size, std::vector<HashFun*> hash_func_list);
	~Bloom();
	void add(const char* text);
	bool check(const char *text);

private:
	const static int CHARBITSIZE = 8;
	int size;
	char *arr;
	vector<HashFun*> hash_func_list;
	inline void set_bit(long pos);
	inline bool get_bit(long pos);
};
#endif
