#include "biome.h"

#include "application/common/debug/debug.h"

using namespace		game;

					biome::biome(enum type type)
{
    int seed = 0;
	switch (this->type = type)
	{
		case (plain) :
			noise = perlin_noise(seed, 0.02f, 7.f);
			first_layer = block_type::dirt_with_grass;
			break ;

        case (desert) :
            noise = perlin_noise(seed, 0.02f, 7.f);
            first_layer = block_type::sand;
            break ;

		case (mountains) :
			noise = perlin_noise(seed, 0.015f, 90.f,  -25.f);
			first_layer = block_type::stone;
			break ;

		default :
			break ;
	}
}

					biome::biome(const biome &other)
{
	type = other.type;
	first_layer = other.first_layer;
	noise = other.noise;
}

bool				::game::operator == (const biome &left, const biome &right)
{
	return left.type == right.type;
}

bool				::game::operator != (const biome &left, const biome &right)
{
	return left.type != right.type;
}

enum biome::type	biome::get_type() const
{
	return type;
}

enum block_type		biome::get_first_layer() const
{
	return first_layer;
}

int 				biome::generate_height(const vec2 &position) const
{
	return (int)noise.generate(position);
}