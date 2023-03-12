cmake_minimum_required(VERSION 3.18.4)

project(template)

# Enforce C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enforce gcc compiler
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
#set(CMAKE_CXX_COMPILER clang++-13)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fmodules")

# Enable Interproceural Optimization, when available
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
if(ipo_supported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION True)
    message("Interprocedural Optimization enabled")
endif()

# Do not permit write on src dir
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed")
endif()

# List compiler features
# list(FIND CMAKE_CXX_COMPILER_FEATURES cxx_std_20 result)
# if(result EQUAL -1)
    # message(FATAL_ERROR "C++20 not supported.")
# endif()    

# Executable
add_executable(template main.cpp)

target_compile_options(template PRIVATE
  -fmodules
  #  -fimplicit-modules
  #-fimplicit-module-maps
)

target_include_directories(template PRIVATE /usr/include/c++/10)

target_link_options(template PRIVATE
  -fmodules
)

target_precompile_headers(template PRIVATE <iostream>)

