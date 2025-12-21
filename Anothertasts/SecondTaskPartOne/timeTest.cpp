#include <chrono>
#include <iostream>
#include "timeTest.hpp"
#include "mergeSort.hpp"

bool checkSorted(int* array, int arraySize) {
    for (int index = 1; index < arraySize; index++) {
        if (array[index] < array[index-1]) return false;
    }
    return true;
}

void timeTest(int* array, int arraySize, int thresholdSize, double* executionTime, bool* isArraySorted) {
    auto startTime = std::chrono::steady_clock::now();
    MergeSort(array, 0, arraySize - 1, thresholdSize);
    auto endTime = std::chrono::steady_clock::now();
    
    std::chrono::duration<double> elapsedTime = endTime - startTime;
    *executionTime = elapsedTime.count();
    *isArraySorted = checkSorted(array, arraySize);
}