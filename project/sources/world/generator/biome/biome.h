#pragma once

#include "common/imports/std.h"
#include "world/block/block/block.h"
#include "world/generator/noise/perlin_noise.h"
#include "world/generator/noise/cellular_noise.h"

namespace					world
{
	class 					biome;
}

class 						world::biome
{
public :

	enum					type
	{
		null,
		test_dirt,
		test_stone
	};

	explicit				biome(enum type type = biome::null);
							biome(const biome &other);

	friend bool 			operator == (const biome &left, const biome &right);
	friend bool 			operator != (const biome &left, const biome &right);

	enum type				get_type() const
	{
		return type;
	}

	enum block::type		get_first_layer() const
	{
		assert(this->type != biome::null);
		return (first_layer);
	}

	int 					generate_height(const vec3 &position) const;

private :

	enum type				type;
	enum block::type		first_layer;

	perlin_noise			noise;
};