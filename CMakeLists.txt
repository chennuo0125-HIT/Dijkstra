cmake_minimum_required(VERSION 2.8.3)
project(dijkstra)
add_compile_options(-std=c++11)

set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_library(dijkstra src/dijkstra.cpp)
add_executable(dijkstra_node src/dijkstra_node.cpp)
target_link_libraries(dijkstra_node dijkstra)