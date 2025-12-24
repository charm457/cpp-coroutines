project(tests)

set(LIBRARY
	bubble_sort_lib
)

add_library(${LIBRARY} "")

add_subdirectory(src)
add_subdirectory(test)