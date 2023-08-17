cmake_minimum_required(VERSION 3.5)

project(Exercise1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

add_executable(temperaturesInput temperaturesInput.cpp)
add_executable(temperaturesFile temperaturesFile.cpp)
