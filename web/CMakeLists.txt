cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(weblse VERSION 1.0)
set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")

add_compile_definitions(NDEBUG)
add_executable(weblse ${CMAKE_CURRENT_SOURCE_DIR}/../src/web.cpp)
target_include_directories(weblse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

#target_link_libraries(weblse PUBLIC
#        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/lev/web/web-build/libweblev.a)
target_include_directories(weblse PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/lev/include)
target_include_directories(weblse PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/lev/src)

set_target_properties(weblse PROPERTIES LINK_FLAGS "-s WASM=1 \
    -03 \
    -lembind \
    -s EXIT_RUNTIME=1")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(weblse PUBLIC Threads::Threads)