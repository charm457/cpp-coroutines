#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <chrono>
#include "voidProverka.hpp"
#include "sortShell.hpp"
using namespace std;
using namespace chrono;


void proverka(vector <int> spisok, vector <int> lst_in) {

    auto start = steady_clock :: now () ;
    vector <int> aa =  shell_sort(spisok, lst_in);
    auto end = steady_clock :: now () ;

    auto start1 = steady_clock :: now () ;
    sort(spisok.begin(), spisok.end());
    auto end1 = steady_clock :: now () ;

    if (aa == spisok) {
        cout << "True" << endl;
        duration <double> elapsed_seconds = end - start;
        duration <double> elapsed_seconds1 = end1 - start1;

        cout << "Shell sort time:" << elapsed_seconds.count() << endl;
        cout << "Standart sort time:" << elapsed_seconds1.count() << endl;
        
    }
    else {
        cout << "False";
    }

}