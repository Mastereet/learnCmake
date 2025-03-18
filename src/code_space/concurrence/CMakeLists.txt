cmake_minimum_required(VERSION 3.18)
project(concurrence)

set(CMAKE_CXX_STANDARD 17)

add_executable(concurrence main.cpp)
target_include_directories(concurrence PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})