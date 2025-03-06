# 设置文件夹名称，用于测试命名前缀
set(FOLDER_NAME "data_structure")

# 添加 MilkVector 接口库
JOT_ADD_LIBRARY(
    NAME milk_vector
    SOURCES
    HEADERS
        milk_vector.hpp
    PUBLIC_LINK_LIBRARIES
    PRIVATE_LINK_LIBRARIES
)

# 添加 MilkVector 测试目标
JOT_ADD_TEST(
    NAME milk_vector_test
    SOURCES
        milk_vector_test.cc
    HEADERS
        milk_vector.hpp
    PUBLIC_LINK_LIBRARIES
        milk_vector
    PRIVATE_LINK_LIBRARIES
        GTest::gtest
        GTest::gtest_main
)