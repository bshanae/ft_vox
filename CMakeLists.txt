# CMake setup

cmake_minimum_required(VERSION 3.10)

# Variables

set(PROJECT_NAME ft_vox)
set(PROJECT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/project)
set(LIBRARIES_DIRECTORY ${PROJECT_DIRECTORY}/libraries)
set(SOURCES_DIRECTORY ${PROJECT_DIRECTORY}/sources)


# Settings

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})

# Headers

include_directories(
	${LIBRARIES_DIRECTORY}
	${LIBRARIES_DIRECTORY}/glad/build/include
	${LIBRARIES_DIRECTORY}/glfw/include
	${LIBRARIES_DIRECTORY}/glm
	${LIBRARIES_DIRECTORY}/stb
	${LIBRARIES_DIRECTORY}/freetype2/include
	${LIBRARIES_DIRECTORY}/FastNoise/Cpp

	${SOURCES_DIRECTORY})

# Sources

set(SOURCES
	# Libraries
	${LIBRARIES_DIRECTORY}/glad/build/src/glad.c

	# Engine : Core
	${SOURCES_DIRECTORY}/engine/core/object/object/object.cpp

	# Engine : Rendering : Main
	${SOURCES_DIRECTORY}/engine/rendering/main/camera/camera.cpp
	${SOURCES_DIRECTORY}/engine/rendering/main/model/model/model.cpp
	${SOURCES_DIRECTORY}/engine/rendering/main/model/texture/texture.cpp
	${SOURCES_DIRECTORY}/engine/rendering/main/program/program/program.cpp
	${SOURCES_DIRECTORY}/engine/rendering/main/program/shader/shader.cpp

	# Engine : Rendering : Ui
	${SOURCES_DIRECTORY}/engine/rendering/ui/button/button.cpp
	${SOURCES_DIRECTORY}/engine/rendering/ui/text/text.cpp
	${SOURCES_DIRECTORY}/engine/rendering/ui/font/symbol/symbol.cpp
	${SOURCES_DIRECTORY}/engine/rendering/ui/font/symbol/symbol_renderer.cpp
	${SOURCES_DIRECTORY}/engine/rendering/ui/font/font/font.cpp

	# Engine : System
	${SOURCES_DIRECTORY}/engine/system/input/input.cpp
	${SOURCES_DIRECTORY}/engine/system/time/timer/timer.cpp
	${SOURCES_DIRECTORY}/engine/system/time/timestamp/timestamp.cpp
	${SOURCES_DIRECTORY}/engine/system/window/window.cpp

	# Engine : Processor
	${SOURCES_DIRECTORY}/engine/processor/processor.cpp

	# Game : World
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/chunk/chunk.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/chunk_renderer/chunk_renderer.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/generator/biome_collection/biome_collection.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/generator/generator/generator.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/generator/biome/biome.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/block/block_alias/block_alias.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/block/block_selector/block_selector.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/block/block_selector/block_selector_renderer.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/block/block/block.cpp
	${SOURCES_DIRECTORY}/game/world/world/world.cpp
	${SOURCES_DIRECTORY}/game/world/utils/texture_atlas/texture_atlas.cpp

	# Game : Player
	${SOURCES_DIRECTORY}/game/player/player.cpp

	# Application : Common
	${SOURCES_DIRECTORY}/application/common/debug/logger/logger.cpp

	# Application : Environment
	${SOURCES_DIRECTORY}/application/environment/environment.cpp
	${SOURCES_DIRECTORY}/application/environment/main.cpp)

# Executable

add_executable(${PROJECT_NAME} ${SOURCES})

# External projects

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${LIBRARIES_DIRECTORY}/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(${LIBRARIES_DIRECTORY}/freetype2)
target_link_libraries(${PROJECT_NAME} freetype)