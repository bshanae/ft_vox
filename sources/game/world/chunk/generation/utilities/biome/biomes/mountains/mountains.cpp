#include "mountains.h"

using namespace		game::biomes;

					mountains::mountains() : snow_generator(0.2f, 0.4f)
{
	height_generator.add_layer(0.008f, 100.f, 3.f);
	height_generator.add_layer(0.08f, 20.f, 1.f);
}

int					mountains::generate_height(const vec2 &column) const
{
	return height_generator(column);
}

game::block_type	mountains::generate_block(int current_height, int total_height, bool is_cave, bool is_cloud) const
{
	if (is_cloud)
		return block_type::cloud;
	else if (is_cave or current_height > total_height)
		return block_type::air;
	else
		return block_type::stone;
}

void				mountains::generate_decoration(const block_ptr &block, bool is_height_affected_by_cave) const
{
	if (not is_height_affected_by_cave and block.get_world_position().y >= (float) snow_level)
	{
		auto		bottom_neighbor = block.get_neighbor(block_face::bottom);

		if (bottom_neighbor and should_replace_stone_with_snowy_stone(bottom_neighbor))
			replace_stone_with_snowy_stone(bottom_neighbor);
	}
}

bool				mountains::should_replace_stone_with_snowy_stone(const block_ptr &block) const
{
	const auto 		block_position = block.get_world_position();

	if (block_position.y >= (float)(snow_level + 10))
		return true;
	else
		return snow_generator({block_position.x, block_position.z});
}

void				mountains::replace_stone_with_snowy_stone(const block_ptr &block) const
{
	block->set_type(block_type::stone_with_snow);
}