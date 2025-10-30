#include <cmath>
#include <cstdlib> 
#include <ctime>   
#include <iostream>

namespace bdk {
    const int SIZE = 20;
    const int REST = 20;

    void generateArray(int *array) {
        for (int index = 0; index < SIZE; index++) {
            array[index] = std::rand() % REST;
            std::cout << array[index];
            std::cout << ' ';
        }
        std::cout << std::endl;
    }

    void processingArray(int *array) {
        int saveValue;
        for (int index = 0; index < SIZE / 2; index++) {
            saveValue = array[index];
            array[index] = array[SIZE - 1 - index];
            array[SIZE - 1 - index] = saveValue;
        }
    }

    void changinArray(int *array) {
        for (int index = 0; index < SIZE; index++) {
            std::cout << array[index];
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    int* array = new int[bdk::SIZE];
    
    std::srand(time(0));

    bdk::generateArray(array);
    bdk::processingArray(array);
    bdk::changinArray(array);
    
    delete[] array;
    return 0;
}