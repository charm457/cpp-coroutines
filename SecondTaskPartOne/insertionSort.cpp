#include "insertionSort.hpp"

void Sortinsertion(int* array, int leftIndex, int rightIndex) {
    for (int currentIndex = leftIndex + 1; currentIndex <= rightIndex; currentIndex++) {
        int keyValue = array[currentIndex];
        int previousIndex = currentIndex - 1;
        
        while (previousIndex >= leftIndex && array[previousIndex] > keyValue) {
            array[previousIndex + 1] = array[previousIndex];
            previousIndex--;
        }
        array[previousIndex + 1] = keyValue;
    }
}