cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME Vox)
project(${PROJECT_NAME})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Project/libraries/glfw/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(SOURCE_FILES
    Project/libraries/glad/src/glad.c
    Project/libraries/FastNoise/FastNoise.cpp

	Project/common/debug.cpp

	Project/core/core/core.cpp
    Project/core/window/window.cpp
	Project/core/object/object.cpp
	Project/core/input/input.cpp

	Project/world/block/texture_atlas.cpp
	Project/world/block/block.cpp
	Project/world/block/block_id.cpp
	Project/world/chunk/chunk.cpp
	Project/world/chunk/chunk_renderer.cpp
	Project/world/chunk/highlighter.cpp
	Project/world/chunk/highlighter_renderer.cpp
	Project/world/chunk/model.cpp
	Project/world/world/world.cpp
	Project/world/program/shader.cpp
	Project/world/program/program.cpp
	Project/world/generator/generator_controller.cpp
	Project/world/generator/plain_generator.cpp
	Project/world/loader/loader.cpp
	Project/world/loader/file.cpp

	Project/player/player/player.cpp
	Project/player/camera/camera.cpp

	Project/application/main.cpp)

set(INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/Project/)
include_directories(
    ${INCLUDES}
    Project/libraries/glad/include)

link_directories(${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/Project/libraries/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/Project/libraries/glfw)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} glfw)
elseif(APPLE)
    find_library(COCOA_Framework Cocoa)
    find_library(OpenGL_Framework OpenGL)
    find_library(IOKit_Framework IOKit)
    find_library(CoreVideo_Framework CoreVideo)

    target_link_libraries(${PROJECT_NAME}
        glfw
        ${COCOA_Framework} ${OpenGL_Framework}
        ${IOKit_Framework} ${CoreVideo_Framework})
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME}
        glfw
        GL
        X11
        pthread
        dl)
endif()
