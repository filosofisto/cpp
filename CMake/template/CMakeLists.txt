cmake_minimum_required(VERSION 3.18.4)

project(changeme)

# Enforce C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
add_executable(changeme main.cpp)
