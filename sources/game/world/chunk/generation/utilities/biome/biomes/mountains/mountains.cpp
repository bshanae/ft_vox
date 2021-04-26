#include "mountains.h"

using namespace		game::biomes;

					mountains::mountains()
{
	height_generator.add_layer(0.008f, 100.f, 3.f);
	height_generator.add_layer(0.08f, 20.f, 1.f);
}

int					mountains::generate_height(const vec2 &column) const
{
	return height_generator(column);
}

game::block_type	mountains::generate_block(int current_height, int total_height) const
{
	if (current_height > total_height)
	{
		return block_type::air;
	}
	else
	{
		if (current_height >= snow_level and current_height == total_height)
        {
		    return block_type::stone_with_snow;
        }
		else
			return block_type::stone;
	}
}

void				mountains::generate_decoration(const block_ptr &block, bool is_height_affected_by_cave) const
{
}