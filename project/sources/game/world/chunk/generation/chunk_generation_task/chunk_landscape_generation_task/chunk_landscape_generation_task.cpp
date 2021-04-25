#include "chunk_landscape_generation_task.h"

#include "game/world/chunk/generation/utilities/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/generation/utilities/biome/biome_generator/biome_generator.h"
#include "game/world/chunk/generation/utilities/height_interpolator/height_interpolator.h"

using namespace			game;

						chunk_landscape_generation_task::chunk_landscape_generation_task() : chunk_generation_task(true)
{}

void 					chunk_landscape_generation_task::do_launch(chunk_workspace &workspace)
{
	generate_chunk(workspace);
}

void 					chunk_landscape_generation_task::generate_chunk(chunk_workspace &workspace)
{
	chunk::index		index;

	for (index.x = 0; index.x < chunk_settings::size[0]; index.x++)
	for (index.z = 0; index.z < chunk_settings::size[2]; index.z++)
	{
		generate_column(workspace, index);
	}
}

void					chunk_landscape_generation_task::generate_column(chunk_workspace &workspace, chunk::index index)
{
	static const auto	height_generator = [](const vec2 &position)
	{
		return biome_generator::generate_biome(position)->generate_height(position);
	};

	const auto			&chunk = workspace.chunk;
	const auto 			column = vec2(chunk->get_position().x + (float)index.x, chunk->get_position().z + (float)index.z);

	const auto			&biome = biome_generator::generate_biome(column);
	const auto			interpolated_height = height_interpolator(height_generator)(column);

	optional<int>		final_height;

	for (index.y = interpolated_height; index.y >= 0; index.y--)
	{
		if (cave_generator(chunk->get_position() + (vec3)index))
		{
			// A cave
		}
		else
		{
			if (not final_height.has_value())
				final_height = index.y;

			chunk->at(index).set_type(biome->generate_block(index.y, interpolated_height));
		}
	}

	if (not final_height.has_value())
		final_height = 0;

	save_calculated_info
	(
		workspace,
		index,
		biome,
		*final_height,
		*final_height != interpolated_height
	);
}

void					chunk_landscape_generation_task::save_calculated_info
						(
							chunk_workspace &workspace,
							chunk::index index,
							const shared_ptr<biomes::abstract> &biome,
							int final_height,
							int is_height_affected_by_cave
						)
{
	auto				&column_info = workspace.column_infos.at({index.x, 0, index.z});

	column_info.biome = biome;
	column_info.final_height = final_height;
	column_info.is_height_affected_by_cave = is_height_affected_by_cave;
}