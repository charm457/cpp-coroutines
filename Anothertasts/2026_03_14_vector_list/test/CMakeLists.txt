add_executable(doubly_linked_list_tests test_doubly_linked_list.cpp templates_doubly_linked_list.cpp)
target_link_libraries(doubly_linked_list_tests 
    gtest_main 
    ${CONTAINERS_LIB}
)
add_test(NAME doubly_linked_list_tests COMMAND doubly_linked_list_tests)

# Тесты для вектора
add_executable(vector_tests test_vector.cpp templates_vector.cpp)
target_link_libraries(vector_tests 
    gtest_main 
    ${CONTAINERS_LIB}
)
add_test(NAME vector_tests COMMAND vector_tests)