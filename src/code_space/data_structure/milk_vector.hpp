#ifndef CODE_SPACE_DATA_STRUCTURE_MILK_VECTOR_HPP
#define CODE_SPACE_DATA_STRUCTURE_MILK_VECTOR_HPP

#include <stdexcept>

namespace milk {

template <typename T>
class MilkVector {
private:
    T* data;         // 指向动态分配的数组内存
    int size;        // 当前元素数量
    int capacity;    // 当前容量

    // 辅助函数：调整容量
    void resize(int new_capacity) {
        T* new_data = new T[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    // 构造函数
    MilkVector(int initial_capacity = 10) 
        : size(0), capacity(initial_capacity) {
        if (initial_capacity < 0) {
            throw std::invalid_argument("Capacity cannot be negative");
        }
        data = new T[capacity];
    }

    // 析构函数
    ~MilkVector() {
        delete[] data;
    }

    // 插入元素到指定位置
    void insert(int index, const T& value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2); // 容量翻倍
        }
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size;
    }

    // 删除指定位置的元素
    void remove(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    // 获取指定位置的元素
    T& get(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // 获取当前大小
    int get_size() const {
        return size;
    }

    // 获取当前容量
    int get_capacity() const {
        return capacity;
    }
};

} // namespace milk

#endif // CODE_SPACE_DATA_STRUCTURE_MILK_VECTOR_HPP