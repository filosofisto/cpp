cmake_minimum_required(VERSION 3.18.4)

project(boost_param01)

# Enforce C++17 standard
set(CMAKE_CXX_STANDARD 17)
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

# Boost Library
set(Boost_INCLUDE_DIR /usr/include/boost)
set(Boost_LIBRARY_DIR /usr/lib/x86_64-linux-gnu/)
find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
set(CMAKE_CXX_FLAGS "-lboost_program_options")

# Executable
add_executable(boost_param01 main.cpp)
target_link_libraries(boost_param01 ${Boost_LIBRARIES})




