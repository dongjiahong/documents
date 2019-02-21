#include "hashfun.h"

class HashFunA : public HashFun {
public:
	virtual long get_hash_val(const char* key) {
		unsigned int h = 0;
		while (*key) {
			h ^= (h<<5) + (h>>2) + (unsigned char)*key++;
		}
		return h%80000;
	}
};

class HashFunB : public HashFun {
public:
	virtual long get_hash_val(const char *key){
		unsigned int h = 0;
		while (*key) {
			h = (unsigned char)*key++ + (h<<6) + (h<<16) - h;
		}
		return h%80000;
	}
};
