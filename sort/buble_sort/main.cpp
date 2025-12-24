#include <iostream>

#include "bubble_sort.hpp"

using namespace std;

int main() {
    int arr[] = {5, 1, 4, 2, 8};
	const int m = sizeof(arr) / sizeof(arr[0]);

    biv::bubble_sort(arr, m);

    for (auto i : arr)
        cout << i << " ";
    return 0;
}