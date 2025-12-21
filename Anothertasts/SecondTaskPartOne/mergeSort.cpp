#include "mergeSort.hpp"
#include "insertionSort.hpp"
#include "merge.hpp"

void MergeSort(int* array, int leftIndex, int rightIndex, int thresholdSize) {
    if (rightIndex - leftIndex + 1 <= thresholdSize) {
        Sortinsertion(array, leftIndex, rightIndex);
        return;
    }

    if (leftIndex < rightIndex) {
        int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;
        MergeSort(array, leftIndex, middleIndex, thresholdSize);
        MergeSort(array, middleIndex + 1, rightIndex, thresholdSize);
        merge(array, leftIndex, middleIndex, rightIndex);
    }
}