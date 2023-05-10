#pragma once

#include <iostream>


template <typename T>
class Vector {
public:
    Vector() : _size(0), _capacity(0), _data(nullptr) {};

    Vector(std::initializer_list<T> values) : _size(values.size()), _capacity(values.size()), _data(new T[values.size()]) {    //  constructor for {...}
        std::move(values.begin(), values.end(), _data);
    };

    Vector(Vector& other) : _size(other._size), _capacity(other._capacity), _data(new T[other._capacity]) {                    //   copy
        for (std::size_t i = 0; i < _size; ++i) {
            new (_data + i) T(other[i]);
        }
    }

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
    void print(std::ostream& os = std::cout) const;

    T* begin() const;
    T* end() const;

private:
    T* _data;

    std::size_t _size;                //  number of elements in my vector  //  64-bit unsigned integer
    std::size_t _capacity;            //  maximum number of elements that vector can hold

    void allocate(size_t item);    // alloc memory for item
    void deallocate();
};

template<typename T>
std::size_t Vector<T>::size() const {
    return _size;
};

template <typename T>
void Vector<T>::allocate(std::size_t newCapacity) {
    if (newCapacity <= _capacity) {
        return;                                     // check if need
    }
    
    T* newData = new T[newCapacity];                // allocate new memory block
    
    for (std::size_t i = 0; i < _size; ++i) {       // in new block
        newData[i] = std::move(_data[i]);
    }
    
    delete[] _data;
    
    _data = newData;
    _capacity = newCapacity;
};

template<typename T>
void Vector<T>::deallocate() {
    if (_data) {       
        delete[] _data;
    }

    _size = 0;
    _capacity = 0;
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

        other.deallocate();
    }

    return *this;
};

template <typename T>
void Vector<T>::reserve(std::size_t capacity) {
    if (capacity > _capacity) {
        T* new_data = allocate(capacity);

        for (std::size_t i = 0; i < _size; ++i) {
            new (new_data + i) T(std::move(_data[i]));              // move the elements to the new array
            //_data[i].~T();                                         // call the destructor for the old elements
        }
        
        deallocate(_data);                                         // deallocate the old array

        _data = new_data;
        _capacity = capacity;
    }
};

template <typename T>
void Vector<T>::pushBack(const T& value) {
    if (_size == _capacity) {
        allocate(_capacity == 0 ? 1 : _capacity * 2);    //  double memory if full, but first 1
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
void Vector<T>::print(std::ostream& os) const {
    os << "[";
    for (std::size_t i = 0; i < _size; ++i) {
        if constexpr (std::is_same_v<T, std::variant<int, double, std::string>>) {
            std::visit([&os](const auto& v){ os << v; }, _data[i]);
        } else {
            os << _data[i];
        }
        if (i != _size - 1) {
            os << ", ";
        }
    }
    os << "]" << std::endl;
}