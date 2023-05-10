#include <ctime>

#include "../inc/overload.hh"
#include "../inc/object.hh"
#include "../inc/core.hh"


int main() {
    std::cout << "* Used memory on programm init: " << memoryUsage << std::endl;

    int maxLines = 500000;
    std::string filePath = "/home/tony/PWR/Cplusplus/sort-some-2/input_rating.tsv";
    std::string fileOut = "/home/tony/PWR/Cplusplus/sort-some-2/output_rating.txt";

    clock_t timeA = clock();

    Core* core = new Core();
    Object<Variant>* object = new Object<Variant>();

    core->readFileInMemory(filePath, maxLines, object);
    core->writeDataInFile(fileOut, object);

    std::cout << "* Max used memory: " << memoryUsage << std::endl;

    //object->print();  <-
    
    delete object;
    delete core;

    clock_t timeB = clock();
    std::cout << "* Total time: " << static_cast<double>(timeB - timeA) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "* Used memory on the end of life cycle: " << memoryUsage << std::endl;
};