#!/bin/bash
mkdir -p bin
rm -f bin/example
g++ main.cpp insertionSort.cpp merge.cpp mergeSort.cpp timeTest.cpp arrayGenerator.cpp -o bin/example && ./bin/example