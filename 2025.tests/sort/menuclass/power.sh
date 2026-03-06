#!/bin/bash
mkdir -p bin
rm -f bin/example
g++ menu_items.cpp menu_func.cpp main.cpp -o bin/example && ./bin/example