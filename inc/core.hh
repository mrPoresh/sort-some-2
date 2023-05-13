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

    void readRatingData(const char* fileName, int maxLines, Vector<RatingData>& ratingVector);
    void writeRatingDataInFile(const char* filePath, Vector<RatingData>& ratingVector);

    void quickSort(Vector<RatingData>& ratingVector, int field);
    void mergeSort(Vector<RatingData>& ratingVector, int field);
    void introSort(Vector<RatingData>& ratingVector, int field);
    void insertionSort(Vector<RatingData>& ratingVector, int field);
    void heapify(Vector<RatingData>& ratingVector, int i, int heapSize, int offset, int field);
    void heapSort(Vector<RatingData>& ratingVector, int low, int high, int field);

    bool compare(const RatingData& a, const RatingData& b, int field);

private:


};

