set(FOLDER_NAME "data_structure")

# once test once JOT_ADD_TEST
JOT_ADD_TEST(
    NAME milk_vector_test
    SOURCES
        milk_vector_test.cc
    HEADERS
        milk_vector.hpp
    PUBLIC_LINK_LIBRARIES

    PRIVATE_LINK_LIBRARIES
        # Add the libraries that this test depends on
)