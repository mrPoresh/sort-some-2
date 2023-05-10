#pragma once

#include <iostream>
#include <variant>

#include "./vector.hh"

using Variant = std::variant<int, double, std::string>;

template <typename T>
class Object {
public:
    Object() : _data() {};

    ~Object() {
        for (auto row : _data) {
            delete row;
            row = nullptr;
        }
    };

    void pushVector(Vector<T>* vector);
    Vector<T>* popVector();
    Vector<T>* back();          // maybe private ?
    std::size_t size() const;
    void print(std::ostream& os = std::cout) const;

private:
    Vector<Vector<T>*> _data;

    std::size_t _size;
};

template <typename T>
void Object<T>::pushVector(Vector<T>* vector) {
    _data.pushBack(vector);

    ++_size;
};

template<typename T>
Vector<T>* Object<T>::popVector() {
    if (_size <= 0) {
        throw std::out_of_range("Vector is empty");
    }

    //Vector<T>* last = back();
    Vector<T>* result = new Vector<T>(std::move(*back()));

    --_size;
    return result;
}

template <typename T>
Vector<T>* Object<T>::back() {
    if (_size == 0) {
        return nullptr;
    }
    return _data[_size - 1];
}

template<typename T>
std::size_t Object<T>::size() const {
    return _size;
};


template <typename T>
void Object<T>::print(std::ostream& os) const {
    for (const auto& vector : _data) {
        vector->print();
    }
}
