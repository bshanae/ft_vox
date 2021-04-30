#include "plain.h"

#include "game/world/chunk/generation/utilities/tree_builder/tree_builder.h"

using namespace		game::biomes;

					plain::plain() :
										generator_tree(0.05f, 0.98f),
										generator_grass(0.5f, 0.80f)
{
	height_generator.add_layer(0.01f, 18.f, 1.f);
	height_generator.add_layer(0.08f, 4.f, 1.f);
}

int					plain::generate_height(const vec2 &column) const
{
	return height_generator(column);
}

game::block_type	plain::generate_block(int current_height, int total_height, bool is_cave, bool is_cloud) const
{
	if (is_cloud)
		return block_type::cloud;
	else if (is_cave or current_height > total_height)
		return block_type::air;
	else if (current_height == total_height)
		return block_type::dirt_with_grass;
	else
		return block_type::dirt;
}

void				plain::generate_decoration(const block_ptr &block, bool is_height_affected_by_cave) const
{
    const auto		block_position = block.get_world_position();
    const auto 		column_position = vec2(block_position.x, block_position.z);

    if (not is_height_affected_by_cave)
    {
		if (generator_tree(column_position))
		{
			if ((int)column_position.x % 7 == 0 and
				(int)column_position.y % 7 == 0)
			{
				tree_builder::build(block);
			}
		}
		else if (generator_grass(column_position))
		{
			block->set_type(block_type::grass);
		}
    }
}