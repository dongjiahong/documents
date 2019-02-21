#include <assert.h>
#include "bloom.h"
#include <iostream>

using namespace std;

Bloom::Bloom(const int &size, vector<HashFun*> hash_func_list) {
	assert(hash_func_list.size() > 0);
	this->size = size;
	this->hash_func_list = hash_func_list;
	this-arr = new char(size);
}

Bloom::~Bloom() {
	if (this->arr != NULL) {
		delete this->arr;
	}
}

void Bloom::add(const char *text) {
	int nfunc = hash_func_list.size();
	long code = 0;
	for (int i=0; i<nfunc; ++i) {
		code = hash_func_list[i]->get_hash_val(text);
		if (code/CHARBITSIZE > size) {
			return;
		} else {
			set_bit(code);
		}
	}
}

bool Bloom::check(const char *text) {
	int nfunc = hash_func_list.size();
	long code = 0;
	for (int i=0; i<nfunc; ++i) {
		code = hash_func_list[i]->get_hash_val(text);
		if (code/CHARBITSIZE > size) {
			return false;
		} else {
			if (get_bit(code)) {
				continue;
			} else {
				return false;
			}
		}
	}
	return true;
}

inline void Bloom::set_bit(long code) {
	arr[code/CHARBITSIZE] |= (1<<(code%CHARBITSIZE))
}

inline bool Bloom::get_bit(long code) {
	if (!arr[code/CHARBITSIZE] & (1<<(code%CHARBITSIZE))) {
		return false;
	}
	return true;
}
