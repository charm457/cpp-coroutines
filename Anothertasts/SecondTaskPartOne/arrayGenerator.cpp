#include <ctime>
#include <random>
#include "arrayGenerator.hpp"

void generateArray(int* array, int arraySize) {
    std::mt19937 randomGenerator(std::time(nullptr));
    for (int index = 0; index < arraySize; index++) {
        array[index] = randomGenerator() % 1000000;
    }
}