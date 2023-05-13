#include "../inc/core.hh"


bool Core::compare(const RatingData& a, const RatingData& b, int field) {
    if (field == 1) {                 
        return a.rank < b.rank;
    } else if (field == 2) {         
        return a.count < b.count;
    } else {
        throw std::invalid_argument("Invalid type: expected float or int"); 
    }
}

void Core::quickSort(Vector<RatingData>& ratingVector, int field) {
    std::function<void(int, int)> qs = [&](int low, int high) {
        if (low < high) {
            // Choose pivot element
            int pivotIndex = (low + high) / 2;
            RatingData pivot = ratingVector[pivotIndex];

            // Partition the data around the pivot
            int i = low - 1;
            int j = high + 1;

            while (true) {
                do {
                    ++i;
                } while (compare(ratingVector[i], pivot, field));
                
                do {
                    --j;
                } while (compare(pivot, ratingVector[j], field));
                
                if (i >= j) {
                    break;
                }
                
                RatingData tmp = std::move(ratingVector[i]);
                ratingVector[i] = std::move(ratingVector[j]);
                ratingVector[j] = std::move(tmp);
            }
            
            // Recursively sort the sub-arrays
            qs(low, j);
            qs(j + 1, high);
        }
    };
    
    qs(0, ratingVector.size() - 1);
};

void Core::mergeSort(Vector<RatingData>& ratingVector, int field) {
    if (ratingVector.size() <= 1) {
        return;
    }

    std::size_t middle = ratingVector.size() / 2;

    Vector<RatingData> left(ratingVector, 0, middle);
    Vector<RatingData> right(ratingVector, middle, ratingVector.size());

    mergeSort(left, field);
    mergeSort(right, field);

    std::size_t i = 0, j = 0, k = 0;

    while (i < left.size() && j < right.size()) {
        if (compare(left[i], right[j], field)) {
            ratingVector[k++] = left[i++];
        } else {
            ratingVector[k++] = right[j++];
        }
    }

    while (i < left.size()) {
        ratingVector[k++] = left[i++];
    }

    while (j < right.size()) {
        ratingVector[k++] = right[j++];
    }
};

void Core::insertionSort(Vector<RatingData>& ratingVector, int field) {
    for (int i = 1; i < ratingVector.size(); ++i) {
        RatingData key = ratingVector[i];
        int j = i - 1;
        
        while (j >= 0 && compare(key, ratingVector[j], field)) {
            ratingVector[j + 1] = ratingVector[j];
            --j;
        }
        
        ratingVector[j + 1] = key;
    }
}

void Core::introSort(Vector<RatingData>& ratingVector, int field) {
    // Determine the maximum recursion depth
    int maxDepth = 2 * log2(ratingVector.size());
    
    std::function<void(int, int, int)> introsortRecursive = [&](int low, int high, int depth) {
        if (high - low > 16) { // Use quicksort for small subarrays
            if (depth == maxDepth) {
                heapSort(ratingVector, low, high, field);
            } else {
                // Choose pivot element
                int pivotIndex = (low + high) / 2;
                RatingData pivot = ratingVector[pivotIndex];
    
                // Partition the data around the pivot
                int i = low - 1;
                int j = high + 1;
    
                while (true) {
                    do {
                        ++i;
                    } while (compare(ratingVector[i], pivot, field));
                    
                    do {
                        --j;
                    } while (compare(pivot, ratingVector[j], field));
                    
                    if (i >= j) {
                        break;
                    }
                    
                    RatingData tmp = std::move(ratingVector[i]);
                    ratingVector[i] = std::move(ratingVector[j]);
                    ratingVector[j] = std::move(tmp);
                }
                
                // Recursively sort the sub-arrays
                introsortRecursive(low, j, depth + 1);
                introsortRecursive(j + 1, high, depth + 1);
            }
        }
    };
    
    introsortRecursive(0, ratingVector.size() - 1, 0);
    
    // Insertion sort the remaining elements
    insertionSort(ratingVector, field);
};

void Core::heapify(Vector<RatingData>& ratingVector, int i, int heapSize, int offset, int field) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < heapSize && compare(ratingVector[offset + left], ratingVector[offset + largest], field)) {
        largest = left;
    }
    
    if (right < heapSize && compare(ratingVector[offset + right], ratingVector[offset + largest], field)) {
        largest = right;
    }
    
    if (largest != i) {
        RatingData tmp = std::move(ratingVector[offset + i]);
        ratingVector[offset + i] = std::move(ratingVector[offset + largest]);
        ratingVector[offset + largest] = std::move(tmp);
        
        heapify(ratingVector, largest, heapSize, offset, field);
    }
};

void Core::heapSort(Vector<RatingData>& ratingVector, int low, int high, int field) {
    // Build max heap
    for (int i = (high - low + 1) / 2 - 1; i >= 0; --i) {
        heapify(ratingVector, i, high - low + 1, low, field);
    }
    
    // Extract elements from the heap
    for (int i = high; i >= low; --i) {
        RatingData tmp = std::move(ratingVector[low]);
        ratingVector[low] = std::move(ratingVector[i]);
        ratingVector[i] = std::move(tmp);
        
        heapify(ratingVector, 0, i - low, low, field);
    }
};

void Core::readRatingData(const char* fileName, int maxLines, Vector<RatingData>& ratingVector) {
    std::ifstream inputFileStream(fileName);

    if (inputFileStream) {
        std::string line;
        std::string headerLine;
        int lineCount = 0;
        ratingVector.reserve(maxLines);

        std::getline(inputFileStream, headerLine);          // dont forget about header line!
        std::stringstream _ss(headerLine);
        std::string headerValue;

        while (std::getline(inputFileStream, line) && lineCount < maxLines) {
            std::stringstream ss(line);
            RatingData data;

            ss >> data.id;
            ss >> data.rank;
            ss >> data.count;

            ratingVector.pushBack(data);
            lineCount++;
        }
    }
};

void Core::writeRatingDataInFile(const char* filePath, Vector<RatingData>& ratingVector) {
    std::ofstream outputFileStream(filePath);

    if (outputFileStream) {
        for (const auto& item : ratingVector) {
            outputFileStream << item.id << " " << item.rank << " " << item.count << "\n";
        }

        outputFileStream.close();
    }
};

