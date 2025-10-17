#include "merge.hpp"
#include <cstdlib>

void merge(int* array, int leftIndex, int middleIndex, int rightIndex) {
    int leftSize = middleIndex - leftIndex + 1;
    int rightSize = rightIndex - middleIndex;
    
    int* leftArray = new int[leftSize];
    int* rightArray = new int[rightSize];
    
    for (int index = 0; index < leftSize; index++)
        leftArray[index] = array[leftIndex + index];
    for (int index = 0; index < rightSize; index++)
        rightArray[index] = array[middleIndex + 1 + index];
    
    int leftPos = 0, rightPos = 0;
    int mergedPos = leftIndex;
    
    while (leftPos < leftSize && rightPos < rightSize) {
        if (leftArray[leftPos] <= rightArray[rightPos]) {
            array[mergedPos] = leftArray[leftPos];
            leftPos++;
        } else {
            array[mergedPos] = rightArray[rightPos];
            rightPos++;
        }
        mergedPos++;
    }
    
    while (leftPos < leftSize) {
        array[mergedPos] = leftArray[leftPos];
        leftPos++;
        mergedPos++;
    }
    
    while (rightPos < rightSize) {
        array[mergedPos] = rightArray[rightPos];
        rightPos++;
        mergedPos++;
    }
    
    delete[] leftArray;
    delete[] rightArray;
}