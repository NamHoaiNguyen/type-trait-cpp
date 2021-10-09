cmake_minimum_required(VERSION 3.16)

project(type_trait VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})

    include_directories("${CMAKE_SOURCE_DIR}/include")

    add_executable(type_trait ${PROJECT_SOURCE_DIR}/test/test.cc)

endif()