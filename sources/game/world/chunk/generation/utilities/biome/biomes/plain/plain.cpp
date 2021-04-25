#include "plain.h"

#include "game/world/chunk/generation/utilities/tree_builder/tree_builder.h"

using namespace		game::biomes;

					plain::plain()
{
	height_generator.add_layer(0.01f, 18.f, 1.f);
	height_generator.add_layer(0.08f, 4.f, 1.f);
}

int					plain::generate_height(const vec2 &column) const
{
	return height_generator(column);
}

game::block_type	plain::generate_block(int current_height, int total_height) const
{
	if (current_height > total_height)
		return block_type::air;
	else if (current_height == total_height)
		return block_type::dirt_with_grass;
	else
		return block_type::dirt;
}

void				plain::generate_decoration(const block_ptr &block, bool is_height_affected_by_cave) const
{
	// This is test
	if ((int)block.get_world_position().x % 50 == 0 and (int)block.get_world_position().z % 50 == 0)
		tree_builder::build(block);
}