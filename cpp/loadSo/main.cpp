#include "work_so.h"
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

	const char *libName		= "./lib/libmethod.so";
	const char *methodName	= "printHello";

	while (true) {
		invoke_method(libName, methodName);
		sleep(1);
	}
}
