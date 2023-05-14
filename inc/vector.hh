#pragma once

#include <iostream>

struct RatingData {
    std::string id;
    float rank = 0;
    int count = 0;
};

struct NameData {
    std::string id;
    std::string primaryTitle;
    std::string originalTitle;
};

struct OutData {
    std::string id;
    std::string primaryTitle;
    std::string originalTitle;
    float rank = 0;
    int count = 0;
};

template <typename T>
class Vector {
public:
    Vector() : _size(0), _capacity(0), _data(nullptr) {};

    Vector(std::initializer_list<T> values) : _size(values.size()), _capacity(values.size()), _data(reinterpret_cast<T*>(new char[values.size() * sizeof(T)])) {    //  constructor for {...}
        auto it = values.begin();

        for (std::size_t i = 0; i < _size; ++i) {
            new (_data + i) T(*it++);
        }
    };

    Vector(Vector& other, int start, int end) : _size(end - start), _capacity(end - start), _data(reinterpret_cast<T*>(new char[(end - start) * sizeof(T)])) {
        for (int i = start; i < end; ++i) {
            new (_data + i - start) T(other[i]);
        }
    }
// i known what im doing
    Vector(Vector& other) : _size(other._size), _capacity(other._capacity), _data(reinterpret_cast<T*>(new char[other._capacity * sizeof(T)])) {//   copy
        for (std::size_t i = 0; i < _size; ++i) {
            new (_data + i) T(other[i]);
        }
    };

    Vector(Vector<T>&& other) noexcept : _size(other._size), _capacity(other._capacity), _data(other._data) {                   //  move constructor
        other._size = 0;
        other._capacity = 0;
        other._data = nullptr;
    };

    ~Vector() { deallocate(); };

    T& operator[](std::size_t index);
    Vector<T>& operator=(const Vector<T>& other);        //  copy assignment operator, vector1 = vector2; This creates a copy of vector2 and replaces the data in vector1 with the data from the copied vector2.
    Vector<T>& operator=(Vector<T>&& other);             //  move assignment operator, takes ownership of the memory used by the other vector.

    std::size_t size() const;

    void reserve(std::size_t capacity);                             //  reserve capacity for the vector
    void pushBack(const T& value);
    void popBack();

    T* begin() const;
    T* end() const;

private:
    T* _data;

    std::size_t _size;                //  number of elements in my vector  //  64-bit unsigned integer
    std::size_t _capacity;            //  maximum number of elements that vector can hold

    void deallocate();
};

template<typename T>
std::size_t Vector<T>::size() const {
    return _size;
};

template <typename T>
void Vector<T>::reserve(std::size_t newCapacity) {
    if (newCapacity <= _capacity) {
        return;                                     // check if need
    }
    
    T* newData = reinterpret_cast<T*>(new char[newCapacity* sizeof(T)]);  // allocate new memory block
    
    for (std::size_t i = 0; i < _size; ++i) {       // in new block
        new (newData + i) T(std::move(_data[i]));
    }
    
    deallocate();
    
    _data = newData;
    _capacity = newCapacity;
};

template<typename T>
void Vector<T>::deallocate() {
    if (_data) {       
        for (std::size_t i = 0; i < _size; ++i) {
            _data[i].~T();
        }

        delete[] reinterpret_cast<char*>(_data);
    }

    _data = nullptr;
};

template<typename T>
T& Vector<T>::operator[](std::size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }

    return _data[index];
};

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        deallocate();
        reserve(other._capacity);

        for (std::size_t i = 0; i < other._size; ++i) {
            new (_data + i) T(other._data[i]);
        }
        _size = other._size;
    }

    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
    if (this != &other) {
        deallocate();

        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;

    }

    return *this;
};

template <typename T>
void Vector<T>::pushBack(const T& value) {
    if (_size == _capacity) {
        reserve(_capacity == 0 ? 1 : _capacity * 2);    //  double memory if full, but first 1
    }

    new (_data + _size) T(value);

    ++_size;
};

template <typename T>
void Vector<T>::popBack() {
    if (_size > 0) {
        _data[--_size].~T();
    }
};

template <typename T>
T* Vector<T>::begin() const {
    return _data;
}

template <typename T>
T* Vector<T>::end() const {
    return _data + _size;
}

template<typename T>
void operator<<(std::ostream& os, Vector<T>& vec) {
    os << "[";
    for (std::size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];

        if (i != vec.size() - 1) {
            os << ", ";
        }
        
    }
    os << "]" << std::endl;
}