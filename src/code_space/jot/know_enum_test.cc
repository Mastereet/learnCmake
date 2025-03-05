#include "jot/know_enum.hpp"
#include <gtest/gtest.h>

enum class TestEnum {
  Apple,
  Banana,
  Orange,
  Pear,
  Pineapple,
  Mango,
  Kiwi,
};

class KnowEnumTest : public ::testing::Test {
protected:
  void SetUp() override { apple = TestEnum::Apple; }
  void TearDown() override {}
  TestEnum apple;
  int invalid_enum_value = 100;
};

TEST_F(KnowEnumTest, GetEnumName) {
  EXPECT_EQ(jot::get_enum_name(apple), "Apple");
  try {
    auto invalied_name = jot::get_enum_name((TestEnum)invalid_enum_value);
  } catch (const std::exception &e) {
    EXPECT_EQ(std::string(e.what()), std::string("Invalid enum value: 100"));
  }
}

TEST_F(KnowEnumTest, EnumFromName) {
  EXPECT_EQ(jot::enum_from_name<TestEnum>("Apple"), TestEnum::Apple);
  EXPECT_EQ(jot::enum_from_name<TestEnum>("Pineapple"), TestEnum::Pineapple);
  EXPECT_EQ(jot::enum_from_name<TestEnum>("Kiwi"), TestEnum::Kiwi);
}

TEST_F(KnowEnumTest, EnumContains) {
    EXPECT_TRUE(jot::enum_contains(TestEnum::Apple));
    EXPECT_TRUE(jot::enum_contains(TestEnum::Pineapple));
    EXPECT_TRUE(jot::enum_contains(TestEnum::Kiwi));
    EXPECT_FALSE(jot::enum_contains((TestEnum)invalid_enum_value));
  }

