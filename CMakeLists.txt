cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME Vox)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/project)
set(PROJECT_EXTERNAL ${PROJECT_ROOT}/external)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})

set(SOURCES_EXTERNAL
	${PROJECT_EXTERNAL}/glad/src/glad.c
	${PROJECT_EXTERNAL}/FastNoise/FastNoise.cpp)

set(SOURCES_ENGINE
	${PROJECT_ROOT}/engine/core/core.cpp
	${PROJECT_ROOT}/engine/window/window.cpp
	${PROJECT_ROOT}/engine/object/object.cpp
	${PROJECT_ROOT}/engine/input/input.cpp
	${PROJECT_ROOT}/engine/program/shader.cpp
	${PROJECT_ROOT}/engine/program/program.cpp
	${PROJECT_ROOT}/engine/model/model.cpp)

set(SOURCES_WORLD
	${PROJECT_ROOT}/world/texture_atlas/texture_atlas.cpp
	${PROJECT_ROOT}/world/block/block.cpp
	${PROJECT_ROOT}/world/block/block_id.cpp
	${PROJECT_ROOT}/world/block/block_selector.cpp
	${PROJECT_ROOT}/world/block/block_selector_renderer.cpp
	${PROJECT_ROOT}/world/chunk/chunk.cpp
	${PROJECT_ROOT}/world/chunk/chunk_renderer.cpp
	${PROJECT_ROOT}/world/world/world.cpp
	${PROJECT_ROOT}/world/generator/generator.cpp
	${PROJECT_ROOT}/world/loader/file.cpp
	${PROJECT_ROOT}/world/loader/loader.cpp)

set(SOURCES_UI
	${PROJECT_ROOT}/ui/font/font.cpp
	${PROJECT_ROOT}/ui/font/symbol.cpp
	${PROJECT_ROOT}/ui/font/symbol_renderer.cpp
	${PROJECT_ROOT}/ui/text/text.cpp
	${PROJECT_ROOT}/ui/button/button.cpp)

set(SOURCES_PLAYER
	${PROJECT_ROOT}/player/player/player.cpp
	${PROJECT_ROOT}/player/camera/camera.cpp)

set(SOURCES_APPLICATION
	${PROJECT_ROOT}/application/main.cpp)

include_directories(
	${PROJECT_ROOT}
	${PROJECT_EXTERNAL}/glad/include
	${PROJECT_EXTERNAL}/glfw/include
	${PROJECT_EXTERNAL}/stb
	${PROJECT_EXTERNAL}/freetype2/include
	${PROJECT_EXTERNAL}/FastNoise)

add_executable(${PROJECT_NAME}
	${SOURCES_EXTERNAL}
	${SOURCES_ENGINE}
	${SOURCES_UI}
	${SOURCES_WORLD}
	${SOURCES_PLAYER}
	${SOURCES_APPLICATION})

add_subdirectory(${PROJECT_EXTERNAL}/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(${PROJECT_EXTERNAL}/freetype2)
target_link_libraries(${PROJECT_NAME} freetype)