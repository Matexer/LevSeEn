cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

project(weblse VERSION 1.0)
set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/public")

add_compile_definitions(NDEBUG)

add_executable(weblse ${CMAKE_CURRENT_SOURCE_DIR}/../src/web.cpp)

#target_link_libraries(weblse PUBLIC
#        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/lev/web/web-build/libweblev.a)
target_include_directories(weblse PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/lev/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/lev/src
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        )

set_target_properties(weblse PROPERTIES LINK_FLAGS "\
    -O3 \
    -lembind \
    -s WASM=1 \
    -s ALLOW_MEMORY_GROWTH=0 \
    -s EXIT_RUNTIME=1 \
    -pthread \
    -s USE_PTHREADS=1 \
    -s PTHREAD_POOL_SIZE=16 \
    -s INITIAL_MEMORY=64MB \
")

target_compile_options(weblse PUBLIC -pthread)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(weblse PUBLIC Threads::Threads)