file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
#add_library(lev STATIC ${SRC_FILES})

add_library(lev STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Distance.cpp)
target_include_directories(lev PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(lev PUBLIC Threads::Threads)
