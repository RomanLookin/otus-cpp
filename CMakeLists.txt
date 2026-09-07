cmake_minimum_required(VERSION 2.8)

project(print_ip)
add_executable(${PROJECT_NAME} "main.cpp")
#set_target_properties(
#        print_ip PROPERTIES
#        CXX_STANDARD 14
#        CXX_STANDARD_REQUIRED ON
#)
set(CMAKE_CXX_EXTENSIONS OFF)      # no vendor-specific extensions
set_property(TARGET print_ip PROPERTY CXX_STANDARD 20)
