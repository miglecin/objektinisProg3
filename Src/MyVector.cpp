#include "MyVector.h"
#include <string>

template <typename T>
MyVector<T>::MyVector() : sz(0), cap(1) {
    arr = new T[cap];
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] arr;
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other) : sz(other.sz), cap(other.cap) {
    arr = new T[cap];
    std::copy(other.arr, other.arr + sz, arr);
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this != &other) {
        delete[] arr;
        sz = other.sz;
        cap = other.cap;
        arr = new T[cap];
        std::copy(other.arr, other.arr + sz, arr);
    }
    return *this;
}

template <typename T>
MyVector<T>::MyVector(MyVector&& other) noexcept : arr(other.arr), sz(other.sz), cap(other.cap) {
    other.arr = nullptr;
    other.sz = 0;
    other.cap = 0;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        delete[] arr;
        arr = other.arr;
        sz = other.sz;
        cap = other.cap;
        other.arr = nullptr;
        other.sz = 0;
        other.cap = 0;
    }
    return *this;
}

template <typename T>
void MyVector<T>::resize_internal() {
    cap *= 2;
    T* new_arr = new T[cap];
    std::copy(arr, arr + sz, new_arr);
    delete[] arr;
    arr = new_arr;
}

template <typename T>
void MyVector<T>::push_back(const T& element) {
    if (sz == cap) {
        resize_internal();
    }
    arr[sz++] = element;
}

template <typename T>
void MyVector<T>::pop_back() {
    if (sz > 0) --sz;
}

template <typename T>
void MyVector<T>::clear() {
    sz = 0;
}

template <typename T>
bool MyVector<T>::empty() const {
    return sz == 0;
}

template <typename T>
void MyVector<T>::resize(size_t new_size) {
    if (new_size > cap) reserve(new_size);
    sz = new_size;
}

template <typename T>
void MyVector<T>::reserve(size_t new_capacity) {
    if (new_capacity > cap) {
        T* new_arr = new T[new_capacity];
        std::copy(arr, arr + sz, new_arr);
        delete[] arr;
        arr = new_arr;
        cap = new_capacity;
    }
}

template <typename T>
void MyVector<T>::assign(size_t n, const T& value) {
    if (n > cap) reserve(n);
    for (size_t i = 0; i < n; ++i) {
        arr[i] = value;
    }
    sz = n;
}

template <typename T>
void MyVector<T>::swap(MyVector& other) noexcept {
    std::swap(arr, other.arr);
    std::swap(sz, other.sz);
    std::swap(cap, other.cap);
}

template <typename T>
size_t MyVector<T>::get_size() const {
    return sz;
}

template <typename T>
size_t MyVector<T>::get_capacity() const {
    return cap;
}

template <typename T>
T& MyVector<T>::operator[](size_t index) {
    return arr[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const {
    return arr[index];
}

template <typename T>
T& MyVector<T>::at(size_t index) {
    if (index >= sz) throw std::out_of_range("Index out of range");
    return arr[index];
}

template <typename T>
const T& MyVector<T>::at(size_t index) const {
    if (index >= sz) throw std::out_of_range("Index out of range");
    return arr[index];
}

template <typename T>
T& MyVector<T>::front() {
    if (sz == 0) throw std::out_of_range("Vector is empty");
    return arr[0];
}

template <typename T>
T& MyVector<T>::back() {
    if (sz == 0) throw std::out_of_range("Vector is empty");
    return arr[sz - 1];
}

template <typename T>
void MyVector<T>::shrink_to_fit() {
    if (sz < cap) {
        T* new_arr = new T[sz];
        std::copy(arr, arr + sz, new_arr);
        delete[] arr;
        arr = new_arr;
        cap = sz;
    }
}

template <typename T>
T* MyVector<T>::begin() {
    return arr;
}

template <typename T>
T* MyVector<T>::end() {
    return arr + sz;
}

template <typename T>
const T* MyVector<T>::begin() const {
    return arr;
}

template <typename T>
const T* MyVector<T>::end() const {
    return arr + sz;
}

// Šablonų instanciacijos
template class MyVector<int>;
template class MyVector<double>;
template class MyVector<std::string>;
