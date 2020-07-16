# CMakeList.txt : CMake project for Phronesis, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.11.0 FATAL_ERROR)
project(Phronesis VERSION 0.1 LANGUAGES CXX)

# Under some compilers CMAKE_DEBUG_POSTFIX is set to "d", we set it to "-d"
set(CMAKE_DEBUG_POSTFIX "-d" CACHE STRING "Set Debug library postfix")
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "Set Release library postfix")
# Removes any dll prefix name on windows, unix will keep a prefix set as "lib"
if(WIN32)
	set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

# Force all compilers to use the correct C++ standard versions.
# Needed to allow for CheckCXXSourceCompiles to work correctly.
set(CMAKE_REQUIRED_FLAGS "-std=c++17")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find source to this project's library.

file(GLOB_RECURSE PHRONESIS_HEADER_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/Sources
		"*.hpp" "*.inl"
		)

file(GLOB_RECURSE PHRONESIS_SOURCE_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/Sources
		"*.cpp"
		)

add_library(Phronesis STATIC ${PHRONESIS_HEADER_FILES} ${PHRONESIS_SOURCE_FILES})

target_include_directories(Phronesis PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Sources
		${CMAKE_CURRENT_SOURCE_DIR}/Sources/External
		)

find_package(Vulkan REQUIRED)
if (Vulkan_FOUND)
	include_directories(${Vulkan_INCLUDE_DIRS})
	target_link_libraries (Phronesis ${Vulkan_LIBRARIES})
else ()
	message(FATAL_ERROR "Could not find Vulkan")
endif ()

find_package(glfw3 3.2 REQUIRED)
#if (GLFW3_FOUND)
	include_directories(${GLFW3_INCLUDE_DIR})
	#link_directories(${GLFW_LIBRARY_DIRS})
	target_link_libraries (Phronesis ${GLFW3_LIBRARY})
	#target_link_libraries (Phronesis glfw)
#else ()
	#message(FATAL_ERROR "Could not find glfw3")
#endif ()

find_package(GLM REQUIRED)
if (GLM_FOUND)
	include_directories(${GLM_INCLUDE_DIR})
else ()
	message(FATAL_ERROR "Could not find glm")
endif ()

install(TARGETS Phronesis DESTINATION ${CMAKE_SOURCE_DIR}/Lib/Linux)
#install(FILES ${PHRONESIS_HEADER_FILES} DESTINATION ${CMAKE_SOURCE_DIR}/Include)
