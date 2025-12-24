#!/bin/bash

BUILD_FOLDER="build_ninja"
SOURCE_FOLDER="sort"

rm -rf "$BUILD_FOLDER"
mkdir -p "$BUILD_FOLDER"
cd "$BUILD_FOLDER" || exit

cmake -G Ninja "../$SOURCE_FOLDER"
ninja

# Копируем нужные файлы
files=("power.sh" "power2.sh" "power3.sh")
folders=("SecondTask15_10_2025" "menuclass" "buble_sort")

for i in {0..1}; do
    src="../$SOURCE_FOLDER/${folders[$i]}/${files[$i]}"
    dst="./${folders[$i]}/${files[$i]}"
    
    if [ -f "$src" ]; then
        mkdir -p "./${folders[$i]}"
        [ ! -f "$dst" ] && cp "$src" "$dst"
    fi
done

[ -f "../run_tests.sh" ] && [ ! -f "./run_tests.sh" ] && cp "../run_tests.sh" "./run_tests.sh"

