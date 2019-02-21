cmake_minimum_required(VERSION 3.3)
project(src_sim)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/include/mysql -lmysqlpp")

set(SOURCE_FILES_MAIN
    baseFile.cpp
    baseFile.h
    loadConfig.cpp
    loadConfig.h
    log.cpp
    log.h
    main.cpp
    QueryRunner.cpp
    QueryRunner.h
    singleton.h
    struct.h
    tools.cpp
    tools.h)
set(SOURCE_FILES_TEST
        test.cpp
        tools.cpp
        QueryRunner.cpp
        )

add_executable(main ${SOURCE_FILES_MAIN})
add_executable(test_fun ${SOURCE_FILES_TEST})