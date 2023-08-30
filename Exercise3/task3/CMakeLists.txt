cmake_minimum_required(VERSION 3.5)

project(task3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

add_executable(commodity commodity_client.cpp commodity.cpp commodity.hpp)
