#include "lakes.h"

using namespace		game::biomes;

					lakes::lakes()
{
	height_generator.add_layer(0.04f, 8.f, 1.f);
	height_generator.add_layer(0.008f, -14.f, 1.f);
}

int					lakes::generate_height(const vec2 &column) const
{
	return height_generator(column);
}

game::block_type	lakes::generate_block(int current_height, int total_height, bool is_cave, bool is_cloud) const
{
	if (is_cloud)
		return block_type::cloud;
	else if (is_cave)
		return generate_block_in_cave(current_height, total_height);
	else if (current_height > total_height)
		return generate_empty_block(current_height, total_height);
	else
		return generate_solid_block(current_height, total_height);
}

void				lakes::generate_decoration(const block_ptr &block, bool is_height_affected_by_cave) const
{
}

game::block_type	lakes::generate_block_in_cave(int current_height, int total_height)
{
	return current_height <= water_level ? block_type::water : block_type::air;
}

game::block_type	lakes::generate_empty_block(int current_height, int total_height)
{
	return current_height <= water_level ? block_type::water : block_type::air;
}

game::block_type	lakes::generate_solid_block(int current_height, int total_height)
{
	if (current_height == total_height and current_height >= water_level)
		return block_type::dirt_with_grass;
	else
		return block_type::dirt;
}