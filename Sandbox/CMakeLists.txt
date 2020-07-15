# CMakeList.txt : CMake project for Sandbox, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.11.0 FATAL_ERROR)
project(Sandbox VERSION 0.1 LANGUAGES CXX)

# Force all compilers to use the correct C++ standard versions.
# Needed to allow for CheckCXXSourceCompiles to work correctly.
set(CMAKE_REQUIRED_FLAGS "-std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find source to this project's executable.

file(GLOB_RECURSE SANDBOX_HEADER_FILES #RELATIVE 
		${CMAKE_CURRENT_SOURCE_DIR}/Sources
		"*.hpp" "*.inl"
		)

file(GLOB_RECURSE SANDBOX_SOURCE_FILES #RELATIVE 
		${CMAKE_CURRENT_SOURCE_DIR}/Sources
		"*.cpp"
		)

#message(STATUS "Sandbox sources at ${CMAKE_CURRENT_SOURCE_DIR}/Sources")

add_executable (Sandbox ${SANDBOX_HEADER_FILES} ${SANDBOX_SOURCE_FILES})

target_include_directories(Sandbox PUBLIC
		${CMAKE_SOURCE_DIR}/Phronesis/Sources
		${CMAKE_SOURCE_DIR}/Phronesis/Sources/External
		)

link_directories(Sandbox PUBLIC
		${CMAKE_SOURCE_DIR}/Lib/Linux
		)

target_link_libraries(Sandbox PUBLIC Phronesis)

install(TARGETS Sandbox DESTINATION ${CMAKE_SOURCE_DIR}/Build-Debug/Linux)
