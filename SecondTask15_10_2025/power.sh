#!/bin/bash
mkdir -p bin
rm -f bin/example
g++ generateArray.cpp processingArray.cpp changinArray.cpp after_refactoring_3.cpp -o bin/example && ./bin/example