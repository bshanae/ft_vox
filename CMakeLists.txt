# CMake setup

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("-pedantic")
add_compile_options("-Ofast")
add_compile_options("-Wno-deprecated-declarations")

project(ft_vox)

# Headers

include_directories(
	project/libraries
	project/libraries/glad/include
	project/libraries/glfw/include
	project/libraries/glm
	project/libraries/stb
	project/libraries/freetype2/include
	project/libraries/FastNoise/Cpp

	project/sources)

# Sources : Libraries

set(SOURCES_LIBRARIES
	project/libraries/glad/src/glad.c)

# Sources : Application

set(SOURCES_APPLICATION
	project/sources/application/common/debug/debug.cpp
	project/sources/application/main.cpp)

# Sources : Engine

set(SOURCES_ENGINE_CORE
	project/sources/engine/main/core/object/object/object.cpp
	project/sources/engine/main/core/object/object_manipulator/object_manipulator.cpp
	project/sources/engine/main/core/object/object_storage/object_storage/object_storage.cpp)

set(SOURCES_ENGINE_RENDERING
	project/sources/engine/main/rendering/layout/layout/layout.cpp
	project/sources/engine/main/rendering/layout/layout_manager/layout_manager.cpp
	project/sources/engine/main/rendering/camera/camera/camera.cpp
	project/sources/engine/main/rendering/model/model/model.cpp
	project/sources/engine/main/rendering/texture/texture/texture.cpp
	project/sources/engine/main/rendering/texture/texture_loader/texture_loader.cpp
	project/sources/engine/main/rendering/texture/cubemap/cubemap.cpp
	project/sources/engine/main/rendering/texture/cubemap_loader/cubemap_loader.cpp
	project/sources/engine/main/rendering/program/program/program.cpp
	project/sources/engine/main/rendering/program/shader/shader.cpp)

set(SOURCES_ENGINE_SYSTEM
	project/sources/engine/main/system/input/input.cpp
	project/sources/engine/main/system/time/timer/timer.cpp
	project/sources/engine/main/system/time/timestamp/timestamp.cpp
	project/sources/engine/main/system/window/window/window.cpp
	project/sources/engine/main/system/window/window_tools/window_tools.cpp)

set(SOURCES_ENGINE_PROCESSOR
	project/sources/engine/main/processor/processor.cpp)

set(SOURCES_ENGINE_LAUNCHER
	project/sources/engine/launcher/launcher.cpp)

set(SOURCES_ENGINE_EXTENSIONS
	project/sources/engine/extensions/utilities/fps_counter/fps_counter.cpp

	project/sources/engine/extensions/ui/text/text.cpp
	project/sources/engine/extensions/ui/font/symbol/symbol.cpp
	project/sources/engine/extensions/ui/font/symbol/symbol_renderer.cpp
	project/sources/engine/extensions/ui/font/font/font.cpp
	project/sources/engine/extensions/ui/font/font_library/font_library.cpp)

set(SOURCES_ENGINE
	${SOURCES_ENGINE_CORE}
	${SOURCES_ENGINE_RENDERING}
	${SOURCES_ENGINE_SYSTEM}
	${SOURCES_ENGINE_PROCESSOR}
	${SOURCES_ENGINE_LAUNCHER}
	${SOURCES_ENGINE_EXTENSIONS})

# Sources : Game

set(SOURCE_GAME_WORLD_BLOCK
	project/sources/game/world/block/block_face/block_face.cpp
	project/sources/game/world/block/block_type/block_type/block_type.cpp
	project/sources/game/world/block/block_ptr/block_ptr.cpp
	project/sources/game/world/block/block_highlighter/block_highlighter/block_highlighter.cpp
	project/sources/game/world/block/block_highlighter/block_highlighter_renderer/block_highlighter_renderer.cpp
	project/sources/game/world/block/block/block.cpp)

set(SOURCE_GAME_WORLD_CHUNK
	project/sources/game/world/chunk/generation/utilities/chunk_workspace/chunk_workspace.cpp
	project/sources/game/world/chunk/generation/utilities/height_generator/height_generator.cpp
	project/sources/game/world/chunk/generation/utilities/height_interpolator/height_interpolator.cpp
	project/sources/game/world/chunk/generation/utilities/decoration_generator/decoration_generator.cpp
	project/sources/game/world/chunk/generation/utilities/cave_generator/cave_generator.cpp
	project/sources/game/world/chunk/generation/utilities/tree_builder/tree_builder.cpp
	project/sources/game/world/chunk/generation/utilities/biome/biome_generator/biome_generator.cpp
	project/sources/game/world/chunk/generation/utilities/biome/biomes/plain/plain.cpp
	project/sources/game/world/chunk/generation/utilities/biome/biomes/desert/desert.cpp
	project/sources/game/world/chunk/generation/utilities/biome/biomes/mountains/mountains.cpp

	project/sources/game/world/chunk/generation/chunk_generation_task/chunk_generation_task/chunk_generation_task.cpp
	project/sources/game/world/chunk/generation/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generation_task.cpp
	project/sources/game/world/chunk/generation/chunk_generation_task/chunk_decoration_generation_task/chunk_decoration_generation_task.cpp
	project/sources/game/world/chunk/generation/chunk_generation_task/chunk_light_generation_task/chunk_light_generation_task.cpp
	project/sources/game/world/chunk/generation/chunk_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task.cpp
	project/sources/game/world/chunk/generation/chunk_generation_task/chunk_geometry_generation_task/tools/ao_calculator/ao_calculator.cpp
	project/sources/game/world/chunk/generation/chunk_generation_task/chunk_model_generation_task/chunk_model_generation_task.cpp

	project/sources/game/world/chunk/generation/chunk_generation_worker/chunk_generation_worker.cpp
	project/sources/game/world/chunk/generation/chunk_generation_director/chunk_generation_director.cpp

	project/sources/game/world/chunk/chunk_renderer/chunk_renderer.cpp

	project/sources/game/world/chunk/chunk/chunk.cpp

	project/sources/game/world/chunk/chunk_map/chunk_map.cpp)

set(SOURCE_GAME_WORLD_SKYBOX
	project/sources/game/world/skybox/skybox.cpp)

set(SOURCE_GAME_WORLD_TEXTURE_ATLAS
	project/sources/game/world/texture_atlas/texture_coordinates/texture_coordinates.cpp
	project/sources/game/world/texture_atlas/texture_atlas/texture_atlas.cpp)

set(SOURCE_GAME_WORLD_WORLD
	project/sources/game/world/world/world.cpp)

set(SOURCE_GAME_PLAYER
	project/sources/game/player/ray_caster/ray_caster.cpp
	project/sources/game/player/player/player.cpp)

set(SOURCE_GAME_LAUNCHER
	project/sources/game/launcher/launcher.cpp)

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

add_executable(ft_vox ${SOURCES})

# External projects

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(project/libraries/glfw)
target_link_libraries(ft_vox glfw)

add_subdirectory(project/libraries/freetype2)
target_link_libraries(ft_vox freetype)