cmake_minimum_required(VERSION 3.5)

project(Exercise3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

add_executable(Circle Circle.cpp)
add_executable(Task4 task4.cpp)

