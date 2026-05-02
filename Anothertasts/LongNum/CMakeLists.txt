cmake_minimum_required(VERSION 3.14)
project(LongNumberProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Указываем пути к исходникам (библиотека в src)
set(LIB_SOURCES 
    src/long_number.cpp 
    src/long_number.hpp
)

# 2. Указываем путь к тестам (в папке tests)
set(TEST_SOURCES 
    tests/main.cpp
)

# 3. Чтобы компилятор видел .hpp файлы внутри src
include_directories(src)

# 4. Создаем библиотеку
add_library(long_number_lib STATIC ${LIB_SOURCES})

# 5. Создаем исполняемый файл
add_executable(unit_tests ${TEST_SOURCES})


target_link_libraries(unit_tests 
    PRIVATE 
    long_number_lib 
    gtest 
    gtest_main 
    pthread
)