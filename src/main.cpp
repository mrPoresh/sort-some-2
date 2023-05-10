#include <ctime>

#include "../inc/overload.hh"
#include "../inc/object.hh"


int main() {
    std::cout << "* Used memory on programm init: " << memoryUsage << std::endl;
    clock_t timeA = clock();

    Object<Variant>* object = new Object<Variant>();

    Vector<Variant>* vector1 = new Vector<Variant>({1, 2.5, "hello"});
    Vector<Variant>* vector2 = new Vector<Variant>({2, 3.5, "World"});

    object->pushVector(vector1);
    object->pushVector(vector2);

    object->print();

    std::cout << "* Max used memory: " << memoryUsage << std::endl;

    clock_t timeB = clock();

    delete object;

    std::cout << "* Total time: " << static_cast<double>(timeB - timeA) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "* Used memory on the end of life cycle: " << memoryUsage << std::endl;
};