#include "MyVector.h"
#include <iostream>

template <typename T>
MyVector<T>::MyVector() : size(0), capacity(1) {
    arr = new T[capacity];
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] arr;
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other) : size(other.size), capacity(other.capacity) {
    arr = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        arr[i] = other.arr[i];
    }
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this == &other) return *this;

    delete[] arr;

    size = other.size;
    capacity = other.capacity;
    arr = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        arr[i] = other.arr[i];
    }

    return *this;
}

template <typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept 
    : arr(other.arr), size(other.size), capacity(other.capacity) {
    other.arr = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this == &other) return *this;

    delete[] arr;

    arr = other.arr;
    size = other.size;
    capacity = other.capacity;

    other.arr = nullptr;
    other.size = 0;
    other.capacity = 0;

    return *this;
}

template <typename T>
void MyVector<T>::resize() {
    capacity *= 2;
    T* new_arr = new T[capacity];
    std::copy(arr, arr + size, new_arr);
    delete[] arr;
    arr = new_arr;
}

template <typename T>
void MyVector<T>::push_back(const T& element) {
    if (size == capacity) {
        resize();
    }
    arr[size++] = element;
}

template <typename T>
void MyVector<T>::pop_back() {
    if (size > 0) {
        --size;
    }
}

template <typename T>
T& MyVector<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}

template <typename T>
size_t MyVector<T>::get_size() const {
    return size;
}

template <typename T>
size_t MyVector<T>::get_capacity() const {
    return capacity;
}

// Explicit template instantiation for commonly used types
template class MyVector<int>;
template class MyVector<double>;
template class MyVector<std::string>;
