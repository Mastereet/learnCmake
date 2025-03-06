#include "data_structure/milk_vector.hpp"
#include <gtest/gtest.h>

namespace milk {

class MilkVectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        vec = MilkVector<int>(5); // 初始容量为 5
        vec.insert(0, 10);
        vec.insert(1, 20);
        vec.insert(2, 30); // 初始状态: [10, 20, 30]
    }

    void TearDown() override {}

    MilkVector<int> vec;
};

TEST_F(MilkVectorTest, Constructor) {
    MilkVector<int> empty_vec; // 默认容量 10
    EXPECT_EQ(empty_vec.get_size(), 0);
    EXPECT_EQ(empty_vec.get_capacity(), 10);

    // 测试负容量异常
    EXPECT_THROW(MilkVector<int> invalid_vec(-1), std::invalid_argument);
}

TEST_F(MilkVectorTest, Insert) {
    // 检查初始状态
    EXPECT_EQ(vec.get_size(), 3);
    EXPECT_EQ(vec.get_capacity(), 5);
    EXPECT_EQ(vec.get(0), 10);
    EXPECT_EQ(vec.get(1), 20);
    EXPECT_EQ(vec.get(2), 30);

    // 插入导致扩容
    vec.insert(3, 40);
    vec.insert(4, 50);
    vec.insert(5, 60); // 容量从 5 扩展到 10
    EXPECT_EQ(vec.get_size(), 6);
    EXPECT_EQ(vec.get_capacity(), 10);
    EXPECT_EQ(vec.get(3), 40);
    EXPECT_EQ(vec.get(4), 50);
    EXPECT_EQ(vec.get(5), 60);

    // 测试异常
    EXPECT_THROW(vec.insert(-1, 100), std::out_of_range);
    EXPECT_THROW(vec.insert(7, 100), std::out_of_range);
}

TEST_F(MilkVectorTest, Remove) {
    // 删除中间元素
    vec.remove(1); // 删除 20，变为 [10, 30]
    EXPECT_EQ(vec.get_size(), 2);
    EXPECT_EQ(vec.get_capacity(), 5);
    EXPECT_EQ(vec.get(0), 10);
    EXPECT_EQ(vec.get(1), 30);

    // 测试异常
    EXPECT_THROW(vec.remove(-1), std::out_of_range);
    EXPECT_THROW(vec.remove(2), std::out_of_range);
}

TEST_F(MilkVectorTest, Get) {
    // 检查初始元素
    EXPECT_EQ(vec.get(0), 10);
    EXPECT_EQ(vec.get(1), 20);
    EXPECT_EQ(vec.get(2), 30);

    // 测试异常
    EXPECT_THROW(vec.get(-1), std::out_of_range);
    EXPECT_THROW(vec.get(3), std::out_of_range);
}

TEST_F(MilkVectorTest, SizeAndCapacity) {
    // 检查初始状态
    EXPECT_EQ(vec.get_size(), 3);
    EXPECT_EQ(vec.get_capacity(), 5);

    // 插入到超出初始容量
    vec.insert(3, 40);
    vec.insert(4, 50);
    vec.insert(5, 60); // 触发扩容
    EXPECT_EQ(vec.get_size(), 6);
    EXPECT_EQ(vec.get_capacity(), 10);

    // 删除元素
    vec.remove(0); // 删除 10
    EXPECT_EQ(vec.get_size(), 5);
    EXPECT_EQ(vec.get_capacity(), 10); // 容量不变
}

} // namespace milk

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}