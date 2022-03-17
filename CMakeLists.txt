cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lse VERSION 1.0)

add_executable(lse ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_include_directories(lse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(lse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/lev/cmake-build-release/liblev.so)
target_include_directories(lse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/lev/include)

set_target_properties(lse
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES)





