#pragma once

#include "common/aliases.h"
#include "common/property.h"
#include "engine/object/unique_object.h"
#include "world/block/block.h"
#include "world/generator/noise.h"

class 						biome
{
public :

	enum					type
	{
		null,
		test_dirt,
		test_stone
	};
							property<read_only, enum type, biome>
							type;

							property<read_only, enum block::type, biome>
							first_layer;

	explicit				biome(enum type type = biome::null)
	{
		switch (this->type.value = type)
		{
			case (test_dirt) :
				noise = ::noise(FastNoise::Perlin, 0.01, 15);
				first_layer = block::type::dirt;
				break ;

			case (test_stone) :
				noise = ::noise(FastNoise::Perlin, 0.01, 40);
				first_layer = block::type::stone;
				break ;

			default :
				break ;
		}

		first_layer.getter = [this]()
		{
			assert(this->type != biome::null);
			return (first_layer.value);
		};
	}

						biome(const biome &other)
	{
		type = other.type;
		first_layer = other.first_layer.value;
		noise = other.noise;
	}

	int 					height(const vec3 &position) const
	{
		assert(type != biome::null);
		return ((int)noise(position));
	}

	friend bool 			operator == (const biome &left, const biome &right)
	{
		return (left.type == right.type);
	}

	friend bool 			operator != (const biome &left, const biome &right)
	{
		return (left.type != right.type);
	}

private :

	noise					noise;
};