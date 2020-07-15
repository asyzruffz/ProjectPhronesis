# CMakeList.txt : CMake project for ProjectPhronesis
#
cmake_minimum_required (VERSION 3.11.0 FATAL_ERROR)
project(ProjectPhronesis VERSION 0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/")
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/")

add_subdirectory(Phronesis)
add_subdirectory(Sandbox)
