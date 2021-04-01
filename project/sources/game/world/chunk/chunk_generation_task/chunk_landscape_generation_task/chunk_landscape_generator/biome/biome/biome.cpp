#include "biome.h"

#include "application/common/debug/debug.h"

using namespace		game;

					biome::biome(enum type type)
{
	switch (this->type = type)
	{
		case (dirt) :
			noise = perlin_noise(1.f, 0.01f, 10.f);
			first_layer = block_type::dirt;
			break ;

		case (grass) :
			noise = perlin_noise(1.f, 0.01f, 10.f);
			first_layer = block_type::grass;
			break ;

        case (sand) :
            noise = perlin_noise(1.f, 0.01f, 10.f);
            first_layer = block_type::sand;
            break ;

		case (stone) :
			noise = perlin_noise(1.f, 0.05f, 30.f);
			first_layer = block_type::stone;
			break ;

		case (rock) :
			noise = perlin_noise(1.f, 0.05f, 30.f);
			first_layer = block_type::rock;
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