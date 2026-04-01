# Создаем библиотеку из твоих .cpp файлов
add_library(${CONTAINERS_LIB} STATIC vector.cpp doubly_linked_list.cpp)

# Указываем, где лежат .hpp файлы, чтобы тесты их видели
target_include_directories(${CONTAINERS_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})