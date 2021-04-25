#include "desert.h"

using namespace		game::biomes;

					desert::desert() :
						height_generator(0.02f, 25.f),
						decoration_generator(0.005f)
{}

int					desert::generate_height(const vec2 &column) const
{
	return height_generator(column);
}

game::block_type	desert::generate_block(int current_height, int total_height) const
{
	if (current_height > total_height)
		return block_type::air;
	else
		return block_type::sand;
}

void				desert::generate_decoration(const block_ptr &block, bool is_height_affected_by_cave) const
{
	const auto		block_position = block.get_world_position();
	const auto 		column_position = vec2(block_position.x, block_position.z);

	if (not is_height_affected_by_cave)
		block->set_type(block_type::blue_flower);
}