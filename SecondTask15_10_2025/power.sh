#!/bin/bash
mkdir -p bin
rm -f bin/example
g++ after_refactoring_3.cpp -o bin/example && ./bin/example