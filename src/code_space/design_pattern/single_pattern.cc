#include "design_pattern/single_pattern.hpp"

// .cpp文件类外初始化
Singleton* Singleton::instance = nullptr;

SingletonMutex* SingletonMutex::instance = nullptr;
std::mutex SingletonMutex::mutex;