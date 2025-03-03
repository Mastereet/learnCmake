cmake_minimum_required(VERSION 3.16)

project(SomeThing LANGUAGES C CXX DESCRIPTION "Just write something casually.")

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable most common warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")


################################################################################
# Include CMake Modules
################################################################################
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Check for compiler flags
include(CheckCXXCompilerFlag)

# Include helper macros and commands, and allow the included file to override
# the CMake policies in this file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeHelper.cmake NO_POLICY_SCOPE)

# Build type
# if not specified, use Release
if(CMAKE_BUILD_TYPE)
    message(STATUS "Build type specified as ${CMAKE_BUILD_TYPE}")
else()
    message(STATUS "Build type not specified, using Release")
    set(CMAKE_BUILD_TYPE Release)
    set(IS_DEBUG OFF)
endif()

