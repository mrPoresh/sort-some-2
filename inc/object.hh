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

template <typename T>
void Object<T>::print(std::ostream& os) const {
    for (const auto& vector : _data) {
        vector->print();
    }
}
