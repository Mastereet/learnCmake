#pragma once

#include <iostream>
#include <mutex>
#include <string>

// 古老的单例模式
class Singleton {
private:
  static Singleton *instance; // 裸指针管理生命周期
  Singleton() {}              // 私有构造函数
public:
  static Singleton *getInstance() {
    // 线程不安全， 若多线程同时调用，会创建多个实例
    if (instance == nullptr) {
      instance = new Singleton(); // 内存泄露隐患
    }
    return instance;
  }
};

// 线程安全的单例模式
class SingletonMutex {
private:
  static SingletonMutex *instance; // 裸指针管理生命周期
  static std::mutex mutex;         // 加入互斥锁
  SingletonMutex() {}              // 私有构造函数
public:
  static SingletonMutex *getInstance() {
    // 线程安全，但是效率低
    if (instance == nullptr) {
      std::lock_guard<std::mutex> lock(mutex); // 确保只有第一个进入的线程进行 new 操作
      if (instance == nullptr) {
        instance = new SingletonMutex(); // 内存泄露隐患
      }
    }
    return instance;
  }

  // 双检锁优化性能
  static SingletonMutex *getInstanceDoubleCheck() {
    if (instance == nullptr) {
      std::lock_guard<std::mutex> lock(mutex);
      if (instance == nullptr) {
        instance = new SingletonMutex();
      }
    }
    return instance;
  }
};

// c++11 保证静态局部变量的初始化是线程安全的
class SingletonCpp11 {
  SingletonCpp11() = default;

public:
  static SingletonCpp11 &getInstance() {
    static SingletonCpp11 instance;
    return instance;
  }
  // 禁止拷贝构造、赋值与移动
  SingletonCpp11(const SingletonCpp11 &) = delete;
  SingletonCpp11 &operator=(const SingletonCpp11 &) = delete;
  SingletonCpp11(SingletonCpp11 &&) = delete;
  SingletonCpp11 &operator=(SingletonCpp11 &&) = delete;
};

// c++ 14 泛型单例
template <typename T>
class SingletonGeneric {
protected:
  SingletonGeneric() = default;

public:
  static auto &getInstance() {
    static T instance;
    return instance;
  }
  SingletonGeneric(const SingletonGeneric &) = delete;
  SingletonGeneric &operator=(const SingletonGeneric &) = delete;
  SingletonGeneric(SingletonGeneric &&) = delete;
  SingletonGeneric &operator=(SingletonGeneric &&) = delete;
};

// usage
class Logger : public SingletonGeneric<Logger> {
  // 使得 SingletonGeneric 可以访问 Logger 的私有构造函数
  friend class SingletonGeneric<Logger>;

private:
  Logger() = default;

public:
  void log(const std::string &msg) { std::cout << msg << std::endl; }
};
