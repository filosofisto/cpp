cmake_minimum_required(VERSION 3.24)
project(copy_constructor_01)

set(CMAKE_CXX_STANDARD 20)

add_executable(copy_constructor_01 main.cpp Person.cpp Person.h)
