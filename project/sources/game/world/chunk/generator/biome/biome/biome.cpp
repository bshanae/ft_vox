#include "biome.h"

#include "application/common/debug/debug.h"

using namespace		game;

					biome::biome(enum type type)
{
	switch (this->type = type)
	{
		case (test_dirt) :
			noise = perlin_noise(1.f, 0.01f, 10.f);
			first_layer = block::dirt;
			break ;

		case (test_stone) :
			noise = perlin_noise(1.f, 0.05f, 30.f);
			first_layer = block::stone;
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

enum block::type	biome::get_first_layer() const
{
	debug::check_critical(type != biome::null, "[game::biome] Bad type");
	return (first_layer);
}

int 				biome::generate_height(const vec3 &position) const
{
	debug::check_critical(type != biome::null, "[game::biome] Bad type");
	return (int)noise.generate(vec2(position.x, position.z));
}