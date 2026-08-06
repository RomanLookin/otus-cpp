cmake_minimum_required(VERSION 3.10.2)

project(tests)

add_executable(${PROJECT_NAME} tests.cpp)

set(CMAKE_CXX_STANDARD 11)

target_link_libraries(${PROJECT_NAME} PUBLIC

helloworld

gtest

gtest_main
)
