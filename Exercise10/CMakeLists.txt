cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include ${PROJECT_SOURCE_DIR}/imgui-sfml/imconfig-SFML.h -std=c++1y -Wall -Wextra -Wno-reorder -Wno-ignored-qualifiers")

if(APPLE)
  add_definitions(-DGL_SILENCE_DEPRECATION)
endif()

find_package(SFML 2.1 COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

find_package(Bullet REQUIRED)
include_directories(${BULLET_INCLUDE_DIRS})

find_package(Threads REQUIRED)

include_directories(imgui imgui-sfml)

add_executable(example main.cpp glut_shapes.c imgui/imgui.cpp imgui/imgui_widgets.cpp imgui/imgui_draw.cpp imgui-sfml/imgui-SFML.cpp)

target_link_libraries(example ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(example ${SFML_LIBRARIES})
target_link_libraries(example ${OPENGL_LIBRARIES})
target_link_libraries(example ${BULLET_LIBRARIES})
