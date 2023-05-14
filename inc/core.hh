#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <cmath>

#include "./vector.hh"


class Core {
public:
    Core() {};
    ~Core() {};

    Vector<OutData>* makeOut(Vector<RatingData>& ratingVector, Vector<NameData>& nameVector);

    void readRatingData(const char* fileName, int maxLines, Vector<RatingData>& ratingVector);
    void readNameData(const char* fileName, int maxLines, Vector<NameData>& nameVector);
    void writeRatingDataInFile(const char* filePath, Vector<RatingData>& ratingVector);
    void writeNameDataInFile(const char* filePath, Vector<NameData>& nameVector);
    void writeOutDataInFile(const char* filePath, Vector<OutData>& outVector);

    void quickSort(Vector<RatingData>& ratingVector, int field);
    void mergeSort(Vector<RatingData>& ratingVector, int field);
    void introSort(Vector<RatingData>& ratingVector, int field);
    void insertionSort(Vector<RatingData>& ratingVector, int field);
    void heapify(Vector<RatingData>& ratingVector, int i, int heapSize, int offset, int field);
    void heapSort(Vector<RatingData>& ratingVector, int low, int high, int field);

    bool compare(const RatingData& a, const RatingData& b, int field);

    int binarySearch(Vector<NameData>& nameVector, const std::string& id);

private:


};

