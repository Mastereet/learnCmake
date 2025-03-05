#include <iostream>
#include <stdexcept>

class Array {
private:
    int *data;
    int size;
    int capacity;

public:
    Array(int cap = 10) : size(0), capacity(cap) {
        data = new int[capacity];
    }

    ~Array() {
        delete[] data;
    }

    void insert(int index, int value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        if (size >= capacity) {
            // 这里可以添加动态调整大小的逻辑，或者在 DynamicArray 中处理
            // 为了简单起见，这里不实现动态调整大小
            throw std::overflow_error("Array is full");
        }
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        size--;
    }

    int get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    int get_size() const {
        return size;
    }

    int get_capacity() const {
        return capacity;
    }
};

class DynamicArray {
private:
    Array arr;
    int capacity;

public:
    DynamicArray(int cap = 10) : arr(10), capacity(cap) {}

    void insert(int index, int value) {
        try {
            arr.insert(index, value);
        } catch (const std::overflow_error &e) {
            // 处理数组已满的情况，进行动态调整大小
            int new_capacity = arr.get_capacity() * 2;
            // 创建一个新的 Array 并复制数据
            Array new_arr(new_capacity);
            for (int i = 0; i < arr.get_size(); ++i) {
                new_arr.insert(i, arr.get(i));
            }
            arr.~Array(); // 销毁旧的 Array
            new ( &arr ) Array(new_capacity); // 重新构造 Array
            for (int i = 0; i < new_arr.get_size(); ++i) {
                arr.insert(i, new_arr.get(i));
            }
            // 重新插入新的值
            arr.insert(index, value);
            capacity = new_capacity;
        }
    }

    void remove(int index) {
        arr.remove(index);
        // 可以根据需要调整容量
        if (arr.get_size() < arr.get_capacity() / 4 && arr.get_capacity() > 10) {
            int new_capacity = arr.get_capacity() / 2;
            Array new_arr(new_capacity);
            for (int i = 0; i < arr.get_size(); ++i) {
                new_arr.insert(i, arr.get(i));
            }
            arr.~Array(); // 销毁旧的 Array
            new ( &arr ) Array(new_capacity); // 重新构造 Array
            for (int i = 0; i < new_arr.get_size(); ++i) {
                arr.insert(i, new_arr.get(i));
            }
            capacity = new_capacity;
        }
    }

    int get(int index) const {
        return arr.get(index);
    }

    void print() const {
        arr.print();
    }

    int get_size() const {
        return arr.get_size();
    }

    int get_capacity() const {
        return capacity;
    }
};

int main() {
    DynamicArray arr;
    for (int i = 0; i < 15; ++i) {
        arr.insert(i, i * 2);
    }
    arr.print(); // 输出: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 

    arr.remove(5);
    arr.print(); // 输出: 0 2 4 6 8 12 14 16 18 20 22 24 26 28 

    std::cout << "Size: " << arr.get_size() << std::endl; // 输出: Size: 14
    std::cout << "Capacity: " << arr.get_capacity() << std::endl; // 输出: Capacity: 20

    return 0;
}