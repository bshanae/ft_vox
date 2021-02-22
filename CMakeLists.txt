# CMake setup

cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_CXX_STANDARD 20)

# '-Wno-deprecated-volatile' is needed because of glm
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wno-deprecated-volatile")

# Variables

set(PROJECT_NAME ft_vox)
set(PROJECT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/project)
set(LIBRARIES_DIRECTORY ${PROJECT_DIRECTORY}/libraries)
set(SOURCES_DIRECTORY ${PROJECT_DIRECTORY}/sources)

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
	${SOURCES_DIRECTORY}/engine/main/core/object/object/object.cpp
	${SOURCES_DIRECTORY}/engine/main/core/object/object_manipulator/object_manipulator.cpp
	${SOURCES_DIRECTORY}/engine/main/core/object/object_storage/object_storage/object_storage.cpp

	# Engine : Rendering
	${SOURCES_DIRECTORY}/engine/main/rendering/layout/layout/layout.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/layout/layout_manager/layout_manager.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/camera/camera/camera.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/model/model/model.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/texture/texture/texture.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/texture/texture_loader/texture_loader.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/texture/cubemap/cubemap.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/texture/cubemap_loader/cubemap_loader.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/program/program/program.cpp
	${SOURCES_DIRECTORY}/engine/main/rendering/program/shader/shader.cpp

	# Engine : System
	${SOURCES_DIRECTORY}/engine/main/system/input/input.cpp
	${SOURCES_DIRECTORY}/engine/main/system/time/timer/timer.cpp
	${SOURCES_DIRECTORY}/engine/main/system/time/timestamp/timestamp.cpp
	${SOURCES_DIRECTORY}/engine/main/system/window/window.cpp

	# Engine : Processor
	${SOURCES_DIRECTORY}/engine/main/processor/processor.cpp

	# Engine : Daemon
	${SOURCES_DIRECTORY}/engine/daemon/daemon.cpp

	# Engine : Extensions
	${SOURCES_DIRECTORY}/engine/extensions/utilities/fps_counter/fps_counter.cpp

	${SOURCES_DIRECTORY}/engine/extensions/ui/text/text.cpp
	${SOURCES_DIRECTORY}/engine/extensions/ui/font/symbol/symbol.cpp
	${SOURCES_DIRECTORY}/engine/extensions/ui/font/symbol/symbol_renderer.cpp
	${SOURCES_DIRECTORY}/engine/extensions/ui/font/font/font.cpp
	${SOURCES_DIRECTORY}/engine/extensions/ui/font/font_library/font_library.cpp

	# Game : World
	${SOURCES_DIRECTORY}/game/world/chunk/block/block_face/block_face.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/block/block_type/block_type/block_type.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/block/block_pointer/block_pointer.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/block/block_highlighter/block_highlighter/block_highlighter.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/block/block_highlighter/block_highlighter_renderer/block_highlighter_renderer.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/block/block/block.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/texture_atlas/texture_coordinates/texture_coordinates.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/texture_atlas/texture_atlas/texture_atlas.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/generation/chunk_workspace/chunk_workspace.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/generation/generators/chunk_landscape_generator/biome/biome_collection/biome_collection.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/generation/generators/chunk_landscape_generator/biome/biome/biome.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/generation/generators/chunk_landscape_generator/chunk_landscape_generator/chunk_landscape_generator.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/generation/generators/chunk_light_generator/chunk_light_generator.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/generation/generators/chunk_geometry_generator/tools/ao_calculator/ao_calculator.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/generation/generators/chunk_geometry_generator/chunk_geometry_generator/chunk_geometry_generator.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/generation/generators/chunk_model_generator/chunk_model_generator.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/generation/chunk_generation_controller/chunk_generation_controller.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/rendering/chunk_renderer/chunk_renderer.cpp
	${SOURCES_DIRECTORY}/game/world/chunk/chunk/chunk/chunk.cpp
	${SOURCES_DIRECTORY}/game/world/world/world.cpp
	${SOURCES_DIRECTORY}/game/world/skybox/skybox.cpp

	# Game : Player
	${SOURCES_DIRECTORY}/game/player/ray_caster/ray_caster.cpp
	${SOURCES_DIRECTORY}/game/player/player/player.cpp

	# Game : Daemon
	${SOURCES_DIRECTORY}/game/daemon/daemon.cpp

	# Application : Application
	${SOURCES_DIRECTORY}/application/common/debug/debug.cpp
	${SOURCES_DIRECTORY}/application/main.cpp)

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