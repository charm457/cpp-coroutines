#!/bin/bash

# Создаем цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}Начинаем сборку игры...${NC}"

# Создаем папку bin, если её нет
if [ ! -d "bin" ]; then
    mkdir -p bin
    echo -e "${GREEN}Создана папка bin${NC}"
fi

# Имя исполняемого файла
EXECUTABLE="bin/mario_game"

# Компиляция
echo -e "${YELLOW}Компиляция mainOOP.cpp...${NC}"
g++ mainOOP.cpp -o $EXECUTABLE -lstdc++ -lncurses -Wall -Wextra

# Проверка успешности компиляции
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Компиляция успешна!${NC}"
    echo -e "${GREEN}✓ Исполняемый файл создан: $EXECUTABLE${NC}"
    
    # Делаем файл исполняемым
    chmod +x $EXECUTABLE
    
    # Показываем размер файла
    SIZE=$(du -h $EXECUTABLE | cut -f1)
    echo -e "${GREEN}✓ Размер файла: $SIZE${NC}"
    
    echo -e "\n${YELLOW}Запустить игру можно командой:${NC}"
    echo -e "./$EXECUTABLE"
    
    # Спрашиваем, запустить ли игру
    read -p "Запустить игру сейчас? (y/n): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        ./$EXECUTABLE
    fi
else
    echo -e "${RED}✗ Ошибка компиляции!${NC}"
    exit 1
