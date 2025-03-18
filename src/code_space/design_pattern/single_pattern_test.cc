#include "design_pattern/single_pattern.hpp"
#include <gtest/gtest.h>

TEST(SingletonTest, Singleton) {
  Singleton* s1 = Singleton::getInstance();
  Singleton* s2 = Singleton::getInstance();
  EXPECT_EQ(s1, s2);
}

TEST(SingletonTest, SingletonMutex) {
  SingletonMutex* s1 = SingletonMutex::getInstance();
  SingletonMutex* s2 = SingletonMutex::getInstance();
  EXPECT_EQ(s1, s2);
}

TEST(SingletonTest, SingletonMutexDoubleCheck) {
  SingletonMutex* s1 = SingletonMutex::getInstanceDoubleCheck();
  SingletonMutex* s2 = SingletonMutex::getInstanceDoubleCheck();
  EXPECT_EQ(s1, s2);
}

TEST(SingletonTest, SingletonCpp11) {
  SingletonCpp11& s1 = SingletonCpp11::getInstance();
  SingletonCpp11& s2 = SingletonCpp11::getInstance();
  EXPECT_EQ(&s1, &s2);
}

TEST(SingletonTest, SingletonGeneric)
{
    auto& logger = Logger::getInstance();
    logger.log("Hello, SingletonGeneric");
    auto& s2 = Logger::getInstance();
    EXPECT_EQ(&logger, &s2);
}