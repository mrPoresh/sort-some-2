#include <ctime>

#include "../inc/overload.hh"
#include "../inc/object.hh"
#include "../inc/core.hh"

#include <vector>

struct Data {
    std::string id;
    float rank = 0;
    int count = 0;
};

void operator<<(std::ostream& os, Data& data) {
    os << "[ ";
    os << data.id << " " << data.rank << " " << data.count;
    os << " ]" << std::endl;
}

void readData(const char* fileName, int maxLines, Vector<Data>& vector) {
    std::ifstream inputFileStream(fileName);

    if (inputFileStream) {
        std::string line;
        std::string headerLine;
        int lineCount = 0;
        vector.reserve(maxLines);

        std::getline(inputFileStream, headerLine);          // dont forget about header line!
        std::stringstream _ss(headerLine);
        std::string headerValue;

        while (std::getline(inputFileStream, line) && lineCount < maxLines) {
            std::stringstream ss(line);
            Data data;

            ss >> data.id;
            ss >> data.rank;
            ss >> data.count;

            vector.pushBack(data);
            lineCount++;
        }
    }
};

int main() {
    std::cout << "* Used memory on programm init: " << memoryUsage << std::endl;

    //int maxLines = 10;
    auto filePath = "/home/tony/PWR/Cplusplus/sort-some-2/input_rating.tsv";
    //std::string fileOut = "/home/tony/PWR/Cplusplus/sort-some-2/output_rating.txt";

    clock_t timeA = clock();

    { Vector<Data> vec;

    readData(filePath, 1000000, vec);
    std::cout << "* Max used memory: " << memoryUsage << std::endl;


    //std::cout << vec;
    }

    clock_t timeB = clock();
    std::cout << "* Total time: " << static_cast<double>(timeB - timeA) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "* Used memory on the end of life cycle: " << memoryUsage << std::endl;
};
