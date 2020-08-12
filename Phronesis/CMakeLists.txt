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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(USE_SFML "Use SFML implementation" OFF)
option(USE_VULKAN "Use Vulkan implementation" ON)
# Use glm and glfw if USE_VULKAN is ON
cmake_dependent_option(USE_GLM "Use glm implementation" ON "USE_VULKAN;NOT USE_SFML" OFF)
cmake_dependent_option(USE_GLFW "Use glfw implementation" ON "USE_VULKAN;NOT USE_SFML" OFF)

# Find source to this project's library.

list(APPEND PHRONESIS_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/StdAfx.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Components.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Components/Camera.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core/Engine.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core/Game.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core/Log.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core/Module.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core/Module.ext.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core/ModuleHandler.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/FileIO.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/FileIO/BinaryFile.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/FileIO/Directory.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Buffer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/CommandBuffer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/CommandPool.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/DescriptorSets.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/FrameBuffers.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/GraphicsPipeline.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Instance.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/LogicalDevice.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/PhysicalDevice.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Pipeline.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/QueueFamilyIndices.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Renderer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/RenderPass.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/RenderUtils.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Shader.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Surface.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/SwapChain.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/UniformBuffer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/UniformBufferObject.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Vertex.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Window.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Maths.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Maths/Matrix4.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Maths/Vector2.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Maths/Vector2.inl
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Maths/Vector3.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Maths/Vector3.inl
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/SceneManagement.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/SceneManagement/Component.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/SceneManagement/Component.ext.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/SceneManagement/Entity.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/SceneManagement/Scene.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/SceneManagement/Scenes.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Utilities.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Utilities/ElapsedTime.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Utilities/String.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Utilities/Time.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Utilities/TimeUpdate.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Utilities/TypeInfo.hpp
	)

list(APPEND PHRONESIS_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/StdAfx.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core/Engine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core/Game.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core/Log.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core/Module.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Core/ModuleHandler.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/FileIO/BinaryFile.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/FileIO/Directory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Buffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/CommandBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/CommandPool.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/DescriptorSets.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/FrameBuffers.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/GraphicsPipeline.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Instance.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/LogicalDevice.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/PhysicalDevice.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Pipeline.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/QueueFamilyIndices.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Renderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/RenderPass.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/RenderUtils.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Shader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Surface.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/SwapChain.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/UniformBuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Vertex.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Window.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Maths/Matrix4.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Maths/Vector2.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Maths/Vector3.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/SceneManagement/Camera.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/SceneManagement/Component.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/SceneManagement/Entity.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/SceneManagement/Scene.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/SceneManagement/Scenes.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Utilities/ElapsedTime.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Utilities/String.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Utilities/Time.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Utilities/TimeUpdate.cpp
	)

# Find external source to this project's library.

set(PHRONESIS_EXT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Sources/External")

file(GLOB_RECURSE PHRONESIS_EXTERNAL_HEADER_FILES
	"${PHRONESIS_EXT_DIR}/*.hpp" "${PHRONESIS_EXT_DIR}/*.inl" "${PHRONESIS_EXT_DIR}/*.h")
list(APPEND PHRONESIS_HEADER_FILES ${PHRONESIS_EXTERNAL_HEADER_FILES})

file(GLOB_RECURSE PHRONESIS_EXTERNAL_SOURCE_FILES
	"${PHRONESIS_EXT_DIR}/*.cpp" "${PHRONESIS_EXT_DIR}/*.c")
list(APPEND PHRONESIS_SOURCE_FILES ${PHRONESIS_EXTERNAL_SOURCE_FILES})

# Find implementation source to this project's library.

if(USE_SFML)
endif()
if(USE_VULKAN)
	list(APPEND PHRONESIS_HEADER_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Platform/VulkanRenderer.hpp)
	list(APPEND PHRONESIS_SOURCE_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Platform/VulkanRenderer.cpp)
endif()
if(USE_GLM)
endif()
if(USE_GLFW)
	list(APPEND PHRONESIS_HEADER_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Platform/GLFWWindow.hpp)
	list(APPEND PHRONESIS_SOURCE_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/Sources/Phronesis/Graphics/Platform/GLFWWindow.cpp)
endif()

# Create target library

add_library(Phronesis STATIC ${PHRONESIS_HEADER_FILES} ${PHRONESIS_SOURCE_FILES})

target_include_directories(Phronesis PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Sources
		${CMAKE_CURRENT_SOURCE_DIR}/Sources/External
		)

if(USE_SFML)
	message(STATUS "Using SFML implementation")
	find_package(SFML 2.5 REQUIRED system window graphics)
	target_link_libraries(Phronesis sfml-system sfml-window sfml-graphics)
	target_compile_definitions(Phronesis PRIVATE USING_SFML)
endif()

if(USE_VULKAN)
	message(STATUS "Using Vulkan implementation")
	find_package(Vulkan REQUIRED)
	if(Vulkan_FOUND)
		include_directories(${Vulkan_INCLUDE_DIRS})
		target_link_libraries (Phronesis ${Vulkan_LIBRARIES})
	else()
		message(FATAL_ERROR "Could not find Vulkan")
	endif()
	target_compile_definitions(Phronesis PRIVATE USING_VULKAN)
endif()

if(USE_GLM)
	message(STATUS "Using glm implementation")
	find_package(GLM REQUIRED)
	if(GLM_FOUND)
		include_directories(${GLM_INCLUDE_DIR})
	else()
		message(FATAL_ERROR "Could not find glm")
	endif()
	target_compile_definitions(Phronesis PRIVATE USING_GLM)
endif()

if(USE_GLFW)
	message(STATUS "Using glfw implementation")
	find_package(glfw3 3.2 REQUIRED)
	#include_directories(${GLFW3_INCLUDE_DIR})
	#target_link_libraries (Phronesis ${GLFW3_LIBRARY})
	target_link_libraries (Phronesis glfw)
	target_compile_definitions(Phronesis PRIVATE USING_GLFW)
endif()

install(TARGETS Phronesis DESTINATION ${CMAKE_SOURCE_DIR}/Lib/Linux)
#install(FILES ${PHRONESIS_HEADER_FILES} DESTINATION ${CMAKE_SOURCE_DIR}/Include)
