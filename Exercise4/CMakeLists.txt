cmake_minimum_required(VERSION 3.5)

project(Exercise4)
INCLUDE(FindPkgConfig)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

pkg_check_modules(GTKMM gtkmm-3.0 REQUIRED)
include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(task1 task1.cpp)
add_executable(task2 task2.cpp)
target_link_libraries(task2 ${GTKMM_LIBRARIES})

