cmake_minimum_required(VERSION 3.0)
project(client)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)