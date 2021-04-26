# CMake setup

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("-pedantic")
add_compile_options("-Ofast")
add_compile_options("-Wno-deprecated-declarations")

project(ft_vox)

# Headers

include_directories(
	libraries
	libraries/glad/include
	libraries/glfw/include
	libraries/glm
	libraries/stb
	libraries/freetype2/include
	libraries/FastNoise/Cpp

	sources)

# Sources : Libraries

set(SOURCES_LIBRARIES
	libraries/glad/src/glad.c)

# Sources : Application

set(SOURCES_APPLICATION
	sources/application/common/debug/debug.cpp
	sources/application/main.cpp)

# Sources : Engine

set(SOURCES_ENGINE_CORE
	sources/engine/main/core/object/object/object.cpp
	sources/engine/main/core/object/object_manipulator/object_manipulator.cpp
	sources/engine/main/core/object/object_storage/object_storage/object_storage.cpp)

set(SOURCES_ENGINE_RENDERING
	sources/engine/main/rendering/layout/layout/layout.cpp
	sources/engine/main/rendering/layout/layout_manager/layout_manager.cpp
	sources/engine/main/rendering/camera/camera/camera.cpp
	sources/engine/main/rendering/model/model/model.cpp
	sources/engine/main/rendering/texture/texture/texture.cpp
	sources/engine/main/rendering/texture/texture_loader/texture_loader.cpp
	sources/engine/main/rendering/texture/cubemap/cubemap.cpp
	sources/engine/main/rendering/texture/cubemap_loader/cubemap_loader.cpp
	sources/engine/main/rendering/program/program/program.cpp
	sources/engine/main/rendering/program/shader/shader.cpp)

set(SOURCES_ENGINE_SYSTEM
	sources/engine/main/system/input/input.cpp
	sources/engine/main/system/time/timer/timer.cpp
	sources/engine/main/system/time/timestamp/timestamp.cpp
	sources/engine/main/system/window/window/window.cpp
	sources/engine/main/system/window/window_tools/window_tools.cpp)

set(SOURCES_ENGINE_PROCESSOR
	sources/engine/main/processor/processor.cpp)

set(SOURCES_ENGINE_LAUNCHER
	sources/engine/launcher/launcher.cpp)

set(SOURCES_ENGINE_EXTENSIONS
	sources/engine/extensions/utilities/fps_counter/fps_counter.cpp

	sources/engine/extensions/ui/text/text.cpp
	sources/engine/extensions/ui/font/symbol/symbol.cpp
	sources/engine/extensions/ui/font/symbol/symbol_renderer.cpp
	sources/engine/extensions/ui/font/font/font.cpp
	sources/engine/extensions/ui/font/font_library/font_library.cpp)

set(SOURCES_ENGINE
	${SOURCES_ENGINE_CORE}
	${SOURCES_ENGINE_RENDERING}
	${SOURCES_ENGINE_SYSTEM}
	${SOURCES_ENGINE_PROCESSOR}
	${SOURCES_ENGINE_LAUNCHER}
	${SOURCES_ENGINE_EXTENSIONS})

# Sources : Game

set(SOURCE_GAME_WORLD_BLOCK
	sources/game/world/block/block_face/block_face.cpp
	sources/game/world/block/block_type/block_type/block_type.cpp
	sources/game/world/block/block_ptr/block_ptr.cpp
	sources/game/world/block/block_highlighter/block_highlighter/block_highlighter.cpp
	sources/game/world/block/block_highlighter/block_highlighter_renderer/block_highlighter_renderer.cpp
	sources/game/world/block/block/block.cpp)

set(SOURCE_GAME_WORLD_CHUNK
	sources/game/world/chunk/generation/utilities/chunk_workspace/chunk_workspace.cpp
	sources/game/world/chunk/generation/utilities/height_generator/height_generator.cpp
	sources/game/world/chunk/generation/utilities/height_interpolator/height_interpolator.cpp
	sources/game/world/chunk/generation/utilities/decoration_generator/decoration_generator.cpp
	sources/game/world/chunk/generation/utilities/cave_generator/cave_generator.cpp
	sources/game/world/chunk/generation/utilities/tree_builder/tree_builder.cpp
	sources/game/world/chunk/generation/utilities/biome/biome_generator/biome_generator.cpp
	sources/game/world/chunk/generation/utilities/biome/biomes/plain/plain.cpp
	sources/game/world/chunk/generation/utilities/biome/biomes/desert/desert.cpp
	sources/game/world/chunk/generation/utilities/biome/biomes/mountains/mountains.cpp

	sources/game/world/chunk/generation/chunk_generation_task/chunk_generation_task/chunk_generation_task.cpp
	sources/game/world/chunk/generation/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generation_task.cpp
	sources/game/world/chunk/generation/chunk_generation_task/chunk_decoration_generation_task/chunk_decoration_generation_task.cpp
	sources/game/world/chunk/generation/chunk_generation_task/chunk_light_generation_task/chunk_light_generation_task.cpp
	sources/game/world/chunk/generation/chunk_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task.cpp
	sources/game/world/chunk/generation/chunk_generation_task/chunk_geometry_generation_task/tools/ao_calculator/ao_calculator.cpp
	sources/game/world/chunk/generation/chunk_generation_task/chunk_model_generation_task/chunk_model_generation_task.cpp

	sources/game/world/chunk/generation/chunk_generation_worker/chunk_generation_worker.cpp
	sources/game/world/chunk/generation/chunk_generation_director/chunk_generation_director.cpp

	sources/game/world/chunk/chunk_renderer/chunk_renderer.cpp

	sources/game/world/chunk/chunk/chunk.cpp

	sources/game/world/chunk/chunk_map/chunk_map.cpp)

set(SOURCE_GAME_WORLD_SKYBOX
	sources/game/world/skybox/skybox.cpp)

set(SOURCE_GAME_WORLD_TEXTURE_ATLAS
	sources/game/world/texture_atlas/texture_coordinates/texture_coordinates.cpp
	sources/game/world/texture_atlas/texture_atlas/texture_atlas.cpp)

set(SOURCE_GAME_WORLD_WORLD
	sources/game/world/world/world.cpp)

set(SOURCE_GAME_PLAYER
	sources/game/player/ray_caster/ray_caster.cpp
	sources/game/player/player/player.cpp)

set(SOURCE_GAME_LAUNCHER
	sources/game/launcher/launcher.cpp)

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
	${SOURCES_GAME} sources/game/world/world/world_settings.h)

# Executable

add_executable(ft_vox ${SOURCES})

# External projects

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libraries/glfw)
target_link_libraries(ft_vox glfw)

add_subdirectory(libraries/freetype2)
target_link_libraries(ft_vox freetype)