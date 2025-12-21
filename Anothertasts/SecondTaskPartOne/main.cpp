#include <cstdlib>
#include <iostream>
#include "insertionSort.hpp"
#include "mergeSort.hpp"
#include "timeTest.hpp"
#include "arrayGenerator.hpp"


int main() {
    const int SMALL_SIZE = 1000;
    const int MEDIUM_SIZE = 10000;
    const int LARGE_SIZE = 100000;
    const int HUGE_SIZE = 1000000;
    
    double minExecutionTime = 10000.0;
    int bestThresholdSize = 0;
    
    int* smallArray = new int[SMALL_SIZE];
    int* mediumArray = new int[MEDIUM_SIZE];
    int* largeArray = new int[LARGE_SIZE];
    int* hugeArray = new int[HUGE_SIZE];
    
    generateArray(smallArray, SMALL_SIZE);
    generateArray(mediumArray, MEDIUM_SIZE);
    generateArray(largeArray, LARGE_SIZE);
    generateArray(hugeArray, HUGE_SIZE);
    
    int* testArrays[] = {smallArray, mediumArray, largeArray, hugeArray};
    int testSizes[] = {SMALL_SIZE, MEDIUM_SIZE, LARGE_SIZE, HUGE_SIZE};
    int testCount = 4;

    for (int testIndex = 0; testIndex < testCount; testIndex++) {
        int* originalArray = testArrays[testIndex];
        int currentArraySize = testSizes[testIndex];
        
        std::cout << "\nРАЗМЕР МАССИВА: " << currentArraySize << std::endl;
        
        for (int thresholdSize = 0; thresholdSize < 10000; thresholdSize += 100) {
            if (thresholdSize < currentArraySize) {
                int* testArrayCopy = new int[currentArraySize];
                for (int index = 0; index < currentArraySize; index++) 
                    testArrayCopy[index] = originalArray[index];
                
                double currentExecutionTime;
                bool isSorted;
                timeTest(testArrayCopy, currentArraySize, thresholdSize, &currentExecutionTime, &isSorted);
                
                if (isSorted) {
                    std::cout << " Yes ";
                } else {
                    std::cout << " No ";
                }
                
                if (minExecutionTime > currentExecutionTime) {
                    minExecutionTime = currentExecutionTime;
                    bestThresholdSize = thresholdSize;
                }
                
                delete[] testArrayCopy;
            }
        }
        std::cout << "Лучший размер порога: " << bestThresholdSize << " Время: " << minExecutionTime << std::endl;
        minExecutionTime = 10000.0;
    }
    
    delete[] smallArray;
    delete[] mediumArray;
    delete[] largeArray;
    delete[] hugeArray;
    
    return 0;
}