methoda:
	g++ -fPIC -shared -o libmethoda.so method_a.cpp
methodb:
	g++ -fPIC -shared -o libmethodb.so method_b.cpp
main:
	g++ main.cpp -L./lib -lmethod -ldl
install:
	cp libmethoda.so ./lib/libmethod.so
addso:
	export LD_LIBRARY_PATH=./lib:${LD_LIBRARY_PATH}
	sudo ldconfig
