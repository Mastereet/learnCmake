set(FOLDER_NAME "design_pattern")

JOT_ADD_LIBRARY(
    NAME design_pattern
    SOURCES
    single_pattern.cc
    HEADERS
    single_pattern.hpp
    PUBLIC_LINK_LIBRARIES
    # Add the libraries that this library depends on
    PRIVATE_LINK_LIBRARIES
    # Add the libraries that this library depends on
)

# once test once JOT_ADD_TEST
JOT_ADD_TEST(
    NAME single_pattern_test
    SOURCES
    single_pattern_test.cc
    HEADERS
    single_pattern.hpp
    PUBLIC_LINK_LIBRARIES

    PRIVATE_LINK_LIBRARIES
    design_pattern
    # Add the libraries that this test depends on
)
