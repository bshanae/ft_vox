#include "mountains.h"

using namespace		game::biomes;

					mountains::mountains() : snow_borders(0.2f, 0.4f)
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
	int 			current_height = block.get_world_position().y;

	if (not is_height_affected_by_cave
		and current_height >= snow_level)
	{
		if (block.get_neighbor(block_face::bottom))
		{
			auto block_bottom = block.get_neighbor(block_face::bottom);

			if (current_height < snow_level + 10)
			{
				const auto		block_position = block_bottom.get_world_position();

				if (snow_borders({block_position.x + block_position.z, block_position.y}))
					block_bottom->set_type(block_type::stone_with_snow);
				else
					block_bottom->set_type(block_type::stone);
			}
			else
				block_bottom->set_type(block_type::stone_with_snow);
		}
	}
}