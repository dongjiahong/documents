#ifndef __HASH_FUN_H__
#define __HASH_FUN_H__

class HashFun {
public:
	virtual long get_hash_val(const char* key) = 0;
};

#endif
