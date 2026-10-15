#!/bin/bash

mkdir -p bin
g++ mainOOP.cpp -o bin/mario_game -lncurses

if [ $? -eq 0 ]; then
    ./bin/mario_game
else
    echo "❌ Ошибка компиляции"
fi