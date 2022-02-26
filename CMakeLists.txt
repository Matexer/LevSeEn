option(WebAssembly OFF)

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lse VERSION 1.0)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/lev)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(lse ${SRC_FILES})

if(WebAssembly)
    message("hfdssfdfsdfsdsdfi")
    set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
    set_target_properties(lse PROPERTIES LINK_FLAGS -s WASM=1 -s EXPORTED_FUNCTIONS='[_main]' -s NO_EXIT_RUNTIME=1 -s EXPORTED_RUNTIME_METHODS=['ccall'])
endif(WebAssembly)

target_include_directories(lse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(lse PUBLIC lev)