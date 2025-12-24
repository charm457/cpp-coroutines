set(SOURCES
    maintest.cpp
)

add_executable(maintest ${SOURCES})  


target_link_libraries(maintest  
    ${LIBRARY}
    gtest_main
    gmock_main
)