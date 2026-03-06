#include <vector>
#include <algorithm>

#include "bubble_sort.hpp"

using namespace std;

void biv::bubble_sort(int* const arr, const int m) {
    for (int i = 0; i < m-1; i++) {     
        for (int j = 0; j < m-i-1; j++) {  
            if (arr[j] > arr[j+1]) {      
                int temp = arr[j];  
                arr[j] = arr[j+1];  
                arr[j+1] = temp;  
            }  
        }  
    }  
}  