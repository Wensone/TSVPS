cmake_minimum_required(VERSION 3.8)
project(BBS)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        v9.cpp)

add_executable(BBS ${SOURCE_FILES})