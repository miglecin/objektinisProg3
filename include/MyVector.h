#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <memory> // for std::allocator


template <typename T>
class MyVector {
private:
    T* arr;
    size_t sz;
    size_t cap;

    void resize_internal();

public:
    using value_type = T;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;

    MyVector();
    ~MyVector();

    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);

    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;

    MyVector(std::initializer_list<T> init) { //initializer_list konstruktorius
    sz = init.size();
    cap = sz;
    arr = new T[cap];
    std::copy(init.begin(), init.end(), arr);
    }

    void push_back(const T& element);
    void pop_back();
    void clear();
    bool empty() const;

    void resize(size_t new_size);
    void reserve(size_t new_capacity);
    void assign(size_t n, const T& value);
    void swap(MyVector& other) noexcept;

    size_t get_size() const;
    size_t get_capacity() const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T& at(size_t index);
    const T& at(size_t index) const;

    T& front();
    T& back();

    void shrink_to_fit();

    // Iterators
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;


    void insert(size_t pos, const T& value) {
        if (pos > sz) throw std::out_of_range("Insert position out of range");
        if (sz == cap) resize_internal();
        for (size_t i = sz; i > pos; --i) arr[i] = arr[i - 1];
        arr[pos] = value;
        ++sz;
    }

    void erase(size_t pos) {
        if (pos >= sz) throw std::out_of_range("Erase position out of range");
        for (size_t i = pos; i < sz - 1; ++i) arr[i] = arr[i + 1];
        --sz;
    }
};

#endif // MYVECTOR_H