#include <ctime>

#include "../inc/overload.hh"
#include "../inc/core.hh"


struct Data {
    std::string id;
    float rank = 0;
    int count = 0;
};

void operator<<(std::ostream& os, RatingData& data) {
    os << "[ ";
    os << data.id << " " << data.rank << " " << data.count;
    os << " ]" << std::endl;
}

int main() {
    clock_t timeA = clock();
    std::cout << "* Used memory on programm init: " << memoryUsage << std::endl;

    int maxLines = 1295000;     //  max 1295000
    auto filePath = "/home/tony/PWR/Cplusplus/sort-some-2/input_rating.tsv";
    auto fileOut = "/home/tony/PWR/Cplusplus/sort-some-2/output_rating.txt";

    Core* core = new Core();
    Vector<RatingData>* ratingVector = new Vector<RatingData>();

    clock_t timeE = clock();
    core->readRatingData(filePath, maxLines, *ratingVector);
    clock_t timeF = clock();
    std::cout << "* Reading data in memory Time: " << static_cast<double>(timeF - timeE) / CLOCKS_PER_SEC << "s" << std::endl;

    clock_t timeC = clock();
    //core->quickSort(*ratingVector, 1);
    //core->mergeSort(*ratingVector, 1);
    core->introSort(*ratingVector, 2);
    clock_t timeD = clock();
    std::cout << "* Sorting Time: " << static_cast<double>(timeD - timeC) / CLOCKS_PER_SEC << "s" << std::endl;

    std::cout << "* Max used memory: " << memoryUsage << std::endl;
    //std::cout << *ratingVector;

    clock_t timeG = clock();
    core->writeRatingDataInFile(fileOut, *ratingVector);
    clock_t timeH = clock();
    std::cout << "* Write data in file Time: " << static_cast<double>(timeH - timeG) / CLOCKS_PER_SEC << "s" << std::endl;

    delete ratingVector;
    delete core;

    clock_t timeB = clock();
    std::cout << "* Total time: " << static_cast<double>(timeB - timeA) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "* Used memory on the end of life cycle: " << memoryUsage << std::endl;
};
