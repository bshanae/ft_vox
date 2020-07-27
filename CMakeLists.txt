cmake_minimum_required(VERSION 3.10)
#set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")
#set(CMAKE_C_COMPILER  "/usr/bin/clang")

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME Vox)
project(${PROJECT_NAME})

add_compile_options(
    -g
    -Wall
    -Wextra

    # -Wpedantic
    # -Wcast-align
    # -Wcast-qual
    # -Wconversion
    # -Wctor-dtor-privacy
    # -Wenum-compare
    # -Wfloat-equal
    # -Wnon-virtual-dtor
    # -Wold-style-cast
    # -Woverloaded-virtual
    # -Wredundant-decls
    # -Wsign-conversion
    # -Wsign-promo
)

# target_compile_features(${PROJECT_NAME} cxx_std_17)

# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Project/libraries/glfw/)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(SOURCE_FILES
    Project/libraries/glad/src/glad.c
    Project/libraries/FastNoise/FastNoise.cpp

	Project/common/debug.cpp

    Project/application/window.cpp
    Project/application/application.cpp
	Project/application/input.cpp
	Project/application/object.cpp

    Project/program/shader.cpp
    Project/program/program.cpp

	Project/camera/camera.cpp

	Project/map/texture_atlas.cpp
    Project/map/model.cpp
	Project/map/map.cpp
	Project/map/chunk.cpp

	Project/renderer/renderer.cpp

    Project/generation/generator_controller.cpp
    Project/generation/plain_generator.cpp

	Project/main.cpp)

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
