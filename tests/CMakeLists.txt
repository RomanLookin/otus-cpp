cmake_minimum_required(VERSION 3.10.2)

project(tests)

add_executable(${PROJECT_NAME} tests.cpp)

set(CMAKE_CXX_STANDARD 11)

add_test(NAME ${PROJECT_NAME} COMMAND tests)
