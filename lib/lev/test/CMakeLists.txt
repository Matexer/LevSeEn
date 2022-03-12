cmake_minimum_required(VERSION 3.21)
project(GTests)

include_directories(${gtest_SOURCE_DIR}/include
                    ${gtest_SOURCE_DIR}
                    ../include
                    ${CMAKE_CURRENT_SOURCE_DIR}/include
                    )

# Testowane kody źródłowe
file(GLOB_RECURSE SRC_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/MultiThread.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Distance.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Search.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Filter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/SelectiveSearch.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/Fix.cpp
        )

file(GLOB_RECURSE TEST_SRC_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/utils.cpp)

add_executable(GTests ${SRC_FILES} ${TEST_SRC_FILES} main.cpp)

set_target_properties(GTests
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(GTests gtest gtest_main Threads::Threads)

