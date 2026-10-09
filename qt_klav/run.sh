#!/usr/bin/env bash
# Запускает собранное приложение. Использование: ./run.sh
set -euo pipefail

# Путь к папке скрипта
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_FOLDER="$SCRIPT_DIR/build_ninja"

# Рабочая папка должна быть build_ninja, т.к. там лежит img/ со смайликом
cd "$BUILD_FOLDER"

if [[ ! -x keyboard ]]; then
    echo "Сначала соберите проект: запустите ./build.sh"
    exit 1
fi

./keyboard