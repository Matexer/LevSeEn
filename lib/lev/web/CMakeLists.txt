cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(weblev VERSION 1.0)
set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")

add_compile_definitions(NDEBUG)
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp)
add_library(weblev STATIC ${SRC_FILES})
target_include_directories(weblev PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

set_target_properties(weblev PROPERTIES LINK_FLAGS "-s WASM=1 -03")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(weblev PUBLIC Threads::Threads)