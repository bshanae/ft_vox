cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME Vox)
project(${PROJECT_NAME})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(FREETYPE REQUIRED)

set(SOURCE_FILES
	Project/common/debug.cpp

	Project/engine/core/core.cpp
    Project/engine/window/window.cpp
	Project/engine/object/object.cpp
	Project/engine/input/input.cpp
	Project/engine/program/shader.cpp
	Project/engine/program/program.cpp

	Project/world/common/model.cpp
	Project/world/block/texture_atlas.cpp
	Project/world/block/block.cpp
	Project/world/block/block_id.cpp
	Project/world/block/block_selector.cpp
	Project/world/block/block_selector_renderer.cpp
	Project/world/chunk/chunk.cpp
	Project/world/chunk/chunk_renderer.cpp
	Project/world/world/world.cpp
	Project/world/generator/generator_controller.cpp
	Project/world/generator/plain_generator.cpp
	Project/world/loader/loader.cpp
	Project/world/loader/file.cpp

	Project/ui/font/symbol.cpp
	Project/ui/font/font.cpp

	Project/player/player/player.cpp
	Project/player/camera/camera.cpp

	Project/application/main.cpp)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/Project
    Project/external/glad/include
	Project/external/freetype2/include)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glew)
target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})

target_link_directories(${PROJECT_NAME} PRIVATE ${ASSIMP_LIBRARY_DIRS})