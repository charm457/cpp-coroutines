#!/bin/bash
mkdir -p bin
rm -f bin/example
g++ main.cpp sortShell.cpp voidProverka.cpp -o bin/example && ./bin/example