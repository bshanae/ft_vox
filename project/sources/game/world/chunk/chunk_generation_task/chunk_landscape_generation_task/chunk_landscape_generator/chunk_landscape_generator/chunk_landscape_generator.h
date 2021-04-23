#pragma once

#include "application/common/imports/std.h"
#include "application/common/imports/glm.h"
#include "application/common/imports/FastNoise.h"

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

#include "game/world/chunk/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generator/noise/cellular_noise.h"
#include "game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generator/biome/biome_collection/biome_collection.h"

namespace				game
{
	class				chunk;
	class				chunk_landscape_generator;
}

class					game::chunk_landscape_generator : public singleton<game::chunk_landscape_generator>
{
public :

	struct				column_info
	{
		const biome		&biome;
		int 			height;
	};

						chunk_landscape_generator();
						~chunk_landscape_generator() override = default;

	static void 		generate_chunk(const shared_ptr<chunk> &workspace);
	static column_info	generate_column(const ivec2 &position);

private :

    int                 seed;

	cellular_noise		noise_for_cell;
	perlin_noise		noise_for_cell_shift;
	random_noise		noise_for_biome;
	perlin_noise		noise_for_clouds;
	perlin_noise		noise_for_snow;
	perlin_noise		noise_for_dungeons;
	perlin_noise		noise_for_mushroom;

	static float	    smoothing_height(const ivec2 &position);
	static void 		generation_dungeons(const shared_ptr<chunk> &chunk, chunk::index index, vec3 position, block_type block_type);
	static void 		generation_clouds(const shared_ptr<chunk> &chunk, vec3 position, chunk::index index);
	static void 		generation_flora(const shared_ptr<chunk> &chunk, vec3 position, chunk::index index, block_type block_type);
	static void 		generation_vertex(const shared_ptr<chunk> &chunk, chunk::index index, vec3 position, block_type block_type);
	static void 		generation_tree(const shared_ptr<chunk> &chunk, chunk::index index);
	const biome			&generate_biome(const vec2 &cell_position);
};


