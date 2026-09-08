cmake_minimum_required(VERSION 2.8)

project(print_ip)
option(WITH_BOOST_TEST "Whether to build Boost test" OFF)
add_executable(${PROJECT_NAME} "main.cpp")
#set_target_properties(
#        print_ip PROPERTIES
#        CXX_STANDARD 14
#        CXX_STANDARD_REQUIRED ON
#)
set(CMAKE_CXX_EXTENSIONS OFF)      # no vendor-specific extensions
set_property(TARGET print_ip PROPERTY CXX_STANDARD 20)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(test_version test_version)
endif()
