cmake_minimum_required(VERSION 3.10)
project(containers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Сначала GTest
add_subdirectory(lib/googletest)

# 2. Имя нашей библиотеки (будет общим для src и test)
set(CONTAINERS_LIB "containers_lib" CACHE INTERNAL "")

# 3. Добавляем папки
add_subdirectory(src)
enable_testing() # Включаем поддержку тестов
add_subdirectory(test)