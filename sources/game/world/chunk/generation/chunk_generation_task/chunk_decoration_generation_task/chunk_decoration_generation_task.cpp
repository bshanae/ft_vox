#include "chunk_decoration_generation_task.h"

#include "game/world/chunk/generation/utilities/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/generation/utilities/height_interpolator/height_interpolator.h"

using namespace			game;

						chunk_decoration_generation_task::chunk_decoration_generation_task() : chunk_generation_task(true)
{}

void 					chunk_decoration_generation_task::do_launch(chunk_workspace &workspace)
{
	generate_decoration_on_chunk(workspace);
}

void 					chunk_decoration_generation_task::generate_decoration_on_chunk(chunk_workspace &workspace)
{
	chunk::index		index;

	for (index.x = 0; index.x < chunk_settings::size[0]; index.x++)
	for (index.z = 0; index.z < chunk_settings::size[2]; index.z++)
	{
		generate_decoration_on_column(workspace, index);
	}
}

void					chunk_decoration_generation_task::generate_decoration_on_column
						(
							chunk_workspace &workspace,
	   						chunk::index index
	   					)
{
	const auto			&chunk = workspace.chunk;
	const auto 			column = vec2(chunk->get_position().x + (float)index.x, chunk->get_position().z + (float)index.z);
	const auto			column_info = workspace.column_infos.at({index.x, 0, index.z});

	const auto			&biome = column_info.biome;
	const auto			block = block_ptr(chunk, {index.x, column_info.final_height + 1, index.z});

	biome->generate_decoration(block, column_info.is_height_affected_by_cave);
}