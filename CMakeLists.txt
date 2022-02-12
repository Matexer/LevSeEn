cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lse VERSION 1.0)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/lev)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(lse ${SRC_FILES})
target_include_directories(lse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(lse PUBLIC lev)