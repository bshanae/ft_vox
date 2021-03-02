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

	static column_info	generate_column(const ivec2 &position);
	static void 		generate_chunk(const shared_ptr<chunk> &workspace);

private :

	cellular_noise		noise_for_biome;

	const biome			&choose_biome(float noise_value);
};


