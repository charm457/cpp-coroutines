if(NOT BUILD_TESTS)
    message(STATUS "Тесты отключены")
    return()
endif()

# Проверяем GoogleTest
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/lib/googletest)
    message(WARNING "GoogleTest не найден! Запустите:")
    message("  mkdir -p lib && cd lib && git clone https://github.com/google/googletest.git")
    return()
endif()

# Подключаем GoogleTest
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/googletest
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest)

# Тестовый файл
add_executable(sorting_tests test_sorting.cpp)

# Подключаем библиотеки
target_link_libraries(sorting_tests
    sorting_algorithms
    gtest_main
)

# Инклюд директории
target_include_directories(sorting_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/sorting/include
)

# Добавляем в CTest
add_test(NAME SortingTests COMMAND sorting_tests)