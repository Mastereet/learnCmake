set(FOLDER_NAME "jot")

JOT_ADD_LIBRARY(
    NAME code_space_jot
    SOURCES

    HEADERS
        know_enum.hpp
    PUBLIC_LINK_LIBRARIES
        # Add the libraries that this library depends on
    PRIVATE_LINK_LIBRARIES
        # Add the libraries that this library depends on
)

# once test once JOT_ADD_TEST
JOT_ADD_TEST(
    NAME jot_know_enum_test
    SOURCES
        know_enum_test.cc
    HEADERS
        know_enum.hpp
    PUBLIC_LINK_LIBRARIES

    PRIVATE_LINK_LIBRARIES
        # Add the libraries that this test depends on
)