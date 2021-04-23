# CMake setup

cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_CXX_STANDARD 17)

add_compile_options("-pedantic")
add_compile_options("-Ofast")
add_compile_options("-frtti")
add_compile_options("-Wno-deprecated-declarations")

# Variables

set(PROJECT_NAME ft_vox)
set(PROJECT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/project)
set(LIBRARIES_DIRECTORY ${PROJECT_DIRECTORY}/libraries)
set(SOURCES_DIRECTORY ${PROJECT_DIRECTORY}/sources)

project(${PROJECT_NAME})

# Headers

include_directories(
	${LIBRARIES_DIRECTORY}
	${LIBRARIES_DIRECTORY}/glad/include
	${LIBRARIES_DIRECTORY}/glfw/include
	${LIBRARIES_DIRECTORY}/glm
	${LIBRARIES_DIRECTORY}/stb
	${LIBRARIES_DIRECTORY}/freetype2/include
	${LIBRARIES_DIRECTORY}/FastNoise/Cpp

	${SOURCES_DIRECTORY})

# Sources : Libraries

set(SOURCES_LIBRARIES
	${LIBRARIES_DIRECTORY}/glad/src/glad.c)

# Sources : Application

set(SOURCES_APPLICATION
	${SOURCES_DIRECTORY}/application/common/debug/debug.cpp
	${SOURCES_DIRECTORY}/application/main.cpp)

# Sources : Engine

set(SOURCES_ENGINE_CORE
	${SOURCES_DIRECTORY}/engine/main/core/object/object/object.cpp
	${SOURCES_DIRECTORY}/engine/main/core/object/object_manipulator/object_manipulator.cpp
	${SOURCES_DIRECTORY}/engine/main/core/object/object_storage/object_storage/object_storage.cpp)

set(SOURCES_ENGINE_RENDERING
	${SOURCES_DIRECTORY}/engine/main/rendering/layout/layout/layout.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/layout/layout_manager/layout_manager.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/camera/camera/camera.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/model/model/model.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/texture/texture/texture.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/texture/texture_loader/texture_loader.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/texture/cubemap/cubemap.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/texture/cubemap_loader/cubemap_loader.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/program/program/program.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/program/shader/shader.cpp)

set(SOURCES_ENGINE_SYSTEM
	${SOURCES_DIRECTORY}/engine/main/system/input/input.cpp
	${SOURCES_DIRECTORY}/engine/main/system/time/timer/timer.cpp
	${SOURCES_DIRECTORY}/engine/main/system/time/timestamp/timestamp.cpp
	${SOURCES_DIRECTORY}/engine/main/system/window/window/window.cpp
	${SOURCES_DIRECTORY}/engine/main/system/window/window_tools/window_tools.cpp)

set(SOURCES_ENGINE_PROCESSOR
	${SOURCES_DIRECTORY}/engine/main/processor/processor.cpp)

set(SOURCES_ENGINE_LAUNCHER
	${SOURCES_DIRECTORY}/engine/launcher/launcher.cpp)

set(SOURCES_ENGINE_EXTENSIONS
	${SOURCES_DIRECTORY}/engine/extensions/utilities/fps_counter/fps_counter.cpp

	${SOURCES_DIRECTORY}/engine/extensions/ui/text/text.cpp
	${SOURCES_DIRECTORY}/engine/extensions/ui/font/symbol/symbol.cpp
	${SOURCES_DIRECTORY}/engine/extensions/ui/font/symbol/symbol_renderer.cpp
	${SOURCES_DIRECTORY}/engine/extensions/ui/font/font/font.cpp
	${SOURCES_DIRECTORY}/engine/extensions/ui/font/font_library/font_library.cpp)

set(SOURCES_ENGINE
	${SOURCES_ENGINE_CORE}
	${SOURCES_ENGINE_RENDERING}
	${SOURCES_ENGINE_SYSTEM}
	${SOURCES_ENGINE_PROCESSOR}
	${SOURCES_ENGINE_LAUNCHER}
	${SOURCES_ENGINE_EXTENSIONS})

# Sources : Game

set(SOURCE_GAME_WORLD_BLOCK
	${SOURCES_DIRECTORY}/game/world/block/block_face/block_face.cpp
	${SOURCES_DIRECTORY}/game/world/block/block_type/block_type/block_type.cpp
	${SOURCES_DIRECTORY}/game/world/block/block_ptr/block_ptr.cpp
	${SOURCES_DIRECTORY}/game/world/block/block_highlighter/block_highlighter/block_highlighter.cpp
	${SOURCES_DIRECTORY}/game/world/block/block_highlighter/block_highlighter_renderer/block_highlighter_renderer.cpp
	${SOURCES_DIRECTORY}/game/world/block/block/block.cpp)

set(SOURCE_GAME_WORLD_CHUNK
	${SOURCES_DIRECTORY}/game/world/chunk/chunk_workspace/chunk_workspace.cpp

	${SOURCES_DIRECTORY}/game/world/chunk/chunk_generation_task/chunk_generation_task/chunk_generation_task.cpp

	${SOURCES_DIRECTORY}/game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generator/biome/biome_collection/biome_collection.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generator/biome/biome/biome.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generator/chunk_landscape_generator/chunk_landscape_generator.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generation_task/chunk_landscape_generation_task.cpp

	${SOURCES_DIRECTORY}/game/world/chunk/chunk_generation_task/chunk_light_generation_task/chunk_light_generation_task.cpp

	${SOURCES_DIRECTORY}/game/world/chunk/chunk_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk_generation_task/chunk_geometry_generation_task/tools/ao_calculator/ao_calculator.cpp

	${SOURCES_DIRECTORY}/game/world/chunk/chunk_generation_task/chunk_model_generation_task/chunk_model_generation_task.cpp

	${SOURCES_DIRECTORY}/game/world/chunk/chunk_generation_worker/chunk_generation_worker.cpp

	${SOURCES_DIRECTORY}/game/world/chunk/chunk_generation_director/chunk_generation_director.cpp

	${SOURCES_DIRECTORY}/game/world/chunk/chunk_renderer/chunk_renderer.cpp

	${SOURCES_DIRECTORY}/game/world/chunk/chunk/chunk.cpp

	${SOURCES_DIRECTORY}/game/world/chunk/chunk_map/chunk_map.cpp)

set(SOURCE_GAME_WORLD_SKYBOX
	${SOURCES_DIRECTORY}/game/world/skybox/skybox.cpp)

set(SOURCE_GAME_WORLD_TEXTURE_ATLAS
	${SOURCES_DIRECTORY}/game/world/texture_atlas/texture_coordinates/texture_coordinates.cpp
	${SOURCES_DIRECTORY}/game/world/texture_atlas/texture_atlas/texture_atlas.cpp)

set(SOURCE_GAME_WORLD_WORLD
	${SOURCES_DIRECTORY}/game/world/world/world.cpp)

set(SOURCE_GAME_PLAYER
	${SOURCES_DIRECTORY}/game/player/ray_caster/ray_caster.cpp
	${SOURCES_DIRECTORY}/game/player/player/player.cpp)

set(SOURCE_GAME_LAUNCHER
	${SOURCES_DIRECTORY}/game/launcher/launcher.cpp)

set(SOURCES_GAME
	${SOURCE_GAME_WORLD_BLOCK}
	${SOURCE_GAME_WORLD_CHUNK}
	${SOURCE_GAME_WORLD_SKYBOX}
	${SOURCE_GAME_WORLD_TEXTURE_ATLAS}
	${SOURCE_GAME_WORLD_WORLD}
	${SOURCE_GAME_PLAYER}
	${SOURCE_GAME_LAUNCHER})

# Sources

set(SOURCES
	${SOURCES_LIBRARIES}
	${SOURCES_APPLICATION}
	${SOURCES_ENGINE}
	${SOURCES_GAME})

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