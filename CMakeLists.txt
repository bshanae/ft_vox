cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME ft_vox)
set(PROJECT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/project)
set(LIBRARIES_FOLDER ${PROJECT_FOLDER}/libraries)
set(SOURCES_FOLDER ${PROJECT_FOLDER}/sources)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})

set(SOURCES_LIBRARIES
	${LIBRARIES_FOLDER}/glad/src/glad.c
	${LIBRARIES_FOLDER}/FastNoise/FastNoise.cpp)

set(SOURCES_COMMON
	${SOURCES_FOLDER}/common/debug/logger/logger.cpp)

set(SOURCES_ENGINE
	${SOURCES_FOLDER}/engine/core/core.cpp
	${SOURCES_FOLDER}/engine/window/window.cpp
	${SOURCES_FOLDER}/engine/object/object/object.cpp
	${SOURCES_FOLDER}/engine/input/input.cpp
	${SOURCES_FOLDER}/engine/program/shader/shader.cpp
	${SOURCES_FOLDER}/engine/program/program/program.cpp
	${SOURCES_FOLDER}/engine/model/model/model.cpp)

set(SOURCES_WORLD
	${SOURCES_FOLDER}/world/texture_atlas/texture_atlas.cpp
	${SOURCES_FOLDER}/world/block/block/block.cpp
	${SOURCES_FOLDER}/world/block/block_id/block_id.cpp
	${SOURCES_FOLDER}/world/block/block_selector/block_selector.cpp
	${SOURCES_FOLDER}/world/block/block_selector/block_selector_renderer.cpp
	${SOURCES_FOLDER}/world/chunk/chunk.cpp
	${SOURCES_FOLDER}/world/chunk/chunk_renderer.cpp
	${SOURCES_FOLDER}/world/world/world.cpp
	${SOURCES_FOLDER}/world/generator/generator/generator.cpp
	${SOURCES_FOLDER}/world/loader/file/file.cpp
	${SOURCES_FOLDER}/world/loader/loader/loader.cpp)

set(SOURCES_UI
	${SOURCES_FOLDER}/ui/font/font/font.cpp
	${SOURCES_FOLDER}/ui/font/symbol/symbol.cpp
	${SOURCES_FOLDER}/ui/font/symbol/symbol_renderer.cpp
	${SOURCES_FOLDER}/ui/text/text.cpp
	${SOURCES_FOLDER}/ui/button/button.cpp)

set(SOURCES_PLAYER
	${SOURCES_FOLDER}/player/player/player.cpp
	${SOURCES_FOLDER}/player/camera/camera.cpp)

set(SOURCES_APPLICATION
	${SOURCES_FOLDER}/application/application.cpp
	${SOURCES_FOLDER}/application/main.cpp)

include_directories(
	${LIBRARIES_FOLDER}
	${LIBRARIES_FOLDER}/glad/include
	${LIBRARIES_FOLDER}/glfw/include
	${LIBRARIES_FOLDER}/glm
	${LIBRARIES_FOLDER}/stb
	${LIBRARIES_FOLDER}/freetype2/include
	${LIBRARIES_FOLDER}/FastNoise

	${SOURCES_FOLDER})

add_executable(${PROJECT_NAME}
	${SOURCES_LIBRARIES}
	${SOURCES_COMMON}
	${SOURCES_ENGINE}
	${SOURCES_UI}
	${SOURCES_WORLD}
	${SOURCES_PLAYER}
	${SOURCES_APPLICATION})

add_subdirectory(${LIBRARIES_FOLDER}/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(${LIBRARIES_FOLDER}/freetype2)
target_link_libraries(${PROJECT_NAME} freetype)