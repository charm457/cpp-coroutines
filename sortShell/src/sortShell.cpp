#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;


vector<int> shell_sort(vector<int> a, vector<int> lst_int) {
    vector<int> interval;
    int s = a.size();

    for (auto i : lst_int) {
        if (i < s) {
            interval.push_back(i);
        }
    }

   
    for (int shag = interval.size() - 1; shag >= 0; shag--) {
        int sdvig = interval[shag];
        
        for (int start = 0; start < sdvig; start++) {
            for (int i = start + sdvig; i < s; i += sdvig) {
                int current = a[i];
                int j = i;

                while (j >= sdvig && a[j - sdvig] > current) {
                    a[j] = a[j - sdvig];
                    j -= sdvig;
                }
                a[j] = current;
            }
        }
    }
    return a;
}


