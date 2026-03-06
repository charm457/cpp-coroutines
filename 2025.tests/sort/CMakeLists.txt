cmake_minimum_required(VERSION 3.2...4.1)
project(cpp-coroutines)

#add_subdirectory(sort)

enable_testing()
add_subdirectory(lib/googletest)


add_subdirectory(tests)
add_subdirectory(menuclass)
add_subdirectory(SecondTask15_10_2025)
add_subdirectory(buble_sort)




set(CMAKE_SUPPRESS_REGENERATION true)