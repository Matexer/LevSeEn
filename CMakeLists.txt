cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lse VERSION 1.0)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/public")
set(LEV_DIR "${CMAKE_SOURCE_DIR}/lib/lev")
set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")

add_executable(lse ${CMAKE_CURRENT_SOURCE_DIR}/src/web.cpp)
target_include_directories(lse PUBLIC ${LEV_DIR}/include)
target_include_directories(lse PUBLIC ${LEV_DIR}/src)
set_target_properties(lse PROPERTIES LINK_FLAGS "-s WASM=1 \
-01 \
-lembind \
-s EXIT_RUNTIME=1 \
-s NO_EXIT_RUNTIME \
-s EXPORTED_FUNCTIONS='' \
-s EXPORTED_RUNTIME_METHODS='ccall, cwrap, stringToUTF8'")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(lse PUBLIC Threads::Threads)

#    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/lev)
#    add_executable(lse ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
#    target_include_directories(lse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
#    target_link_libraries(lse PUBLIC lev)
