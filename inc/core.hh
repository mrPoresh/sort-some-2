#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "./object.hh"


class Core {
public:
    Core() {};
    ~Core() {};

    void readFileInMemory(const std::string& filePath, int maxLines, Object<Variant>* object);
    void writeDataInFile(const std::string& filePath, Object<Variant>* object);

private:

};

