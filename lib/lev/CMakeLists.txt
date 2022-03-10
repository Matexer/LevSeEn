cmake_minimum_required(VERSION 3.21)
project(lev)

#file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
#add_library(lev STATIC ${SRC_FILES})
add_library(lev STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Distance.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/Search.cpp)

target_include_directories(lev PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(test)

set_target_properties(lev
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(lev PUBLIC Threads::Threads)
