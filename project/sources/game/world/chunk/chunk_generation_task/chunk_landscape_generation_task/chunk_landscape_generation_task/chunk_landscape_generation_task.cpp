#include "chunk_landscape_generation_task.h"

#include "game/world/chunk/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generator/chunk_landscape_generator/chunk_landscape_generator.h"

using namespace		game;

					chunk_landscape_generation_task::chunk_landscape_generation_task() : chunk_generation_task(true)
{}

void 				chunk_landscape_generation_task::do_launch(chunk_workspace &workspace)
{
	chunk_landscape_generator::generate_chunk(workspace.chunk);
}