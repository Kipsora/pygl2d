cmake_minimum_required(VERSION 3.9)
project(pygl2d C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_COMPILER clang)

add_library(pygl2d SHARED src/library.c src/library.h)
add_executable(test-c src/library.h src/library.c test.c)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(pygl2d ${GLFW_LIBRARIES})
target_link_libraries(test-c ${GLFW_LIBRARIES})
target_link_libraries(pygl2d ${GLFW_STATIC_LIBRARIES})
target_link_libraries(test-c ${GLFW_STATIC_LIBRARIES})

find_package (GLEW REQUIRED STATIC)
target_link_libraries(pygl2d ${GLEW_LIBRARIES})
target_link_libraries(test-c ${GLEW_LIBRARIES})

find_library(GL_LIBARIES OpenGL)
target_link_libraries(pygl2d ${GL_LIBARIES})
target_link_libraries(test-c ${GL_LIBARIES})
