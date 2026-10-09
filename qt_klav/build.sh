#!/usr/bin/env bash
# Собирает проект Qt6 под Linux. Работает из любой папки: ./build.sh
set -euo pipefail

# Путь к папке скрипта
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

BUILD_TYPE=Ninja
BUILD_SUFFIX=ninja
BUILD_FOLDER="build_${BUILD_SUFFIX}"
IMG_FOLDER=img

# Qt6 ищем через cmake; если пакет не найден — подсказываем установку
if ! command -v cmake >/dev/null 2>&1; then
    echo "cmake не найден. Установите: sudo apt install cmake (или pacman -S cmake)"
    exit 1
fi

if ! command -v ninja >/dev/null 2>&1; then
    # Нет ninja — переключаемся на обычные makefiles
    BUILD_TYPE="Unix Makefiles"
fi

mkdir -p "$BUILD_FOLDER"

cmake -G "$BUILD_TYPE" -S "$SCRIPT_DIR" -B "$SCRIPT_DIR/$BUILD_FOLDER"
cmake --build "$SCRIPT_DIR/$BUILD_FOLDER"

# Картинка со смайликом нужна рядом с бинарником (см. run.sh)
mkdir -p "$BUILD_FOLDER/$IMG_FOLDER"
cp -f "$SCRIPT_DIR/$IMG_FOLDER/grustnii-smail.png" "$BUILD_FOLDER/$IMG_FOLDER/"

echo "Готово: $BUILD_FOLDER/keyboard"