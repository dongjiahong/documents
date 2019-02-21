main:
	clang++ -Wall -std=c++11 main.cpp loadConfig.cpp log.cpp tools.cpp QueryRunner.cpp \
		createLog.cpp \
		-I/usr/include/mysql -lmysqlpp -omain
test:
	clang++ -Wall -std=c++11 test.cpp tools.cpp QueryRunner.cpp createLog.cpp\
		-I/usr/include/mysql -lmysqlpp -otest
clean:
	rm main test
