#pragma once

#include "application/common/imports/std.h"

#include "game/world/block/block/block.h"
#include "game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generator/noise/perlin_noise.h"
#include "game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generator/noise/cellular_noise.h"

namespace					game
{
	class 					biome;
}

class 						game::biome
{
public :

	enum					type
	{
		null,
		dirt,
		grass,
        sand,
		stone,
		snow,
		mushroom,
		tree,
        cloud
	};

	explicit				biome(enum type type = biome::null);
							biome(const biome &other);

	friend bool 			operator == (const biome &left, const biome &right);
	friend bool 			operator != (const biome &left, const biome &right);

	enum type				get_type() const;
	enum block_type			get_first_layer() const;

	int 					generate_height(const vec2 &position) const;

private :

	enum type				type;
	enum block_type			first_layer;

	perlin_noise			noise;
};