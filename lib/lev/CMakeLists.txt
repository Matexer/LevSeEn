file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(lev STATIC ${SRC_FILES} src/search.cpp)
target_include_directories(lev PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)