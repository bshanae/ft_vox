#include "biome.h"

#include "application/common/debug/debug.h"

using namespace		game;

					biome::biome(enum type type)
{
    int seed = 0;
	switch (this->type = type)
	{
		case (dirt) :
			noise = perlin_noise(seed, 0.03f, 13.f);
			first_layer = block_type::dirt;
			break ;

		case (grass) :
			noise = perlin_noise(seed, 0.02f, 7.f);
			first_layer = block_type::grass;
			break ;

        case (sand) :
            noise = perlin_noise(seed, 0.02f, 7.f);
            first_layer = block_type::sand;
            break ;

		case (stone) :
			noise = perlin_noise(seed, 0.015f, 90.f,  -25.f);
			first_layer = block_type::stone;
			break ;

		case (cloud) :
			first_layer = block_type::cloud;
			break ;

		case (snow) :
            noise = perlin_noise(seed, 0.015f);
			first_layer = block_type::snow;
			break ;

		case (mushroom) :
			first_layer = block_type::mushroom;
			break ;

		case (tree) :
			first_layer = block_type::tree;
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
	debug::check_critical(type != biome::null, "[biome] Bad type");
	return first_layer;
}

int 				biome::generate_height(const vec2 &position) const
{
	debug::check_critical(type != biome::null, "[biome] Bad type");
	return (int)noise.generate(position);
}