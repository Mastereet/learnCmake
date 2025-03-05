cmake_minimum_required(VERSION 3.16)

project(SomeThing LANGUAGES C CXX DESCRIPTION "Just write something casually.")

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable most common warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# enable test
option(TESTS_ENABLED "Whether to enable tests" ON)

set(CODE_SPACE_INCLUDR_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

if(TESTS_ENABLED)
    include(GoogleTest)
    enable_testing()
endif()


################################################################################
# Include CMake Modules
################################################################################
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Check for compiler flags
include(CheckCXXCompilerFlag)

# Include helper macros and commands, and allow the included file to override
# the CMake policies in this file
include(cmake/CMakeHelper.cmake NO_POLICY_SCOPE)

################################################################################
# Dependency configuration
################################################################################
# Find the required libraries
set(JOT_FIND_QUIETLY FALSE)
include(cmake/FindDependencies.cmake)


# Build type
# if not specified, use Release
if(CMAKE_BUILD_TYPE)
    message(STATUS "Build type specified as ${CMAKE_BUILD_TYPE}")
else()
    message(STATUS "Build type not specified, using Release")
    set(CMAKE_BUILD_TYPE Release)
    set(IS_DEBUG OFF)
endif()
include_directories(${CODE_SPACE_INCLUDR_DIRS})

add_subdirectory(jot)

