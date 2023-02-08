cmake_minimum_required(VERSION 3.24)
project(object_pool_01)

set(CMAKE_CXX_STANDARD 20)

add_executable(object_pool_01 main.cpp ObjectPool.cpp ObjectPool.h ExpensiveObject.cpp ExpensiveObject.h)
