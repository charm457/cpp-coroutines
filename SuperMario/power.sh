#!/bin/bash

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}================================${NC}"
echo -e "${GREEN}   Mario Game Launcher${NC}"
echo -e "${GREEN}================================${NC}"


# Компиляция
echo -e "${YELLOW}Compiling game...${NC}"
gcc -o mario_game mainCopyWrite.c -lm -lncurses

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Compilation successful!${NC}"
    echo -e "${YELLOW}Starting game...${NC}"
    echo -e "${GREEN}================================${NC}"
    sleep 1
    
    # Запуск игры
    ./mario_game
    
    # Очистка после игры
    clear
    echo -e "${GREEN}================================${NC}"
    echo -e "${GREEN}Game exited!${NC}"
    echo -e "${GREEN}================================${NC}"
else
    echo -e "${RED}Compilation failed!${NC}"
    exit 1
fi