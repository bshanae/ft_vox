#include "tree_builder.h"

#include "game/world/chunk/generation/utilities/noise/random_noise_1d.h"


using namespace		game;

void				tree_builder::build(const block_ptr &block)
{
	random_noise_1d	random(FT_VOX_SEED);
	int				delta;

	block_ptr		trunk_block = block;
	block_ptr		leave_block;

	for (int y = 0; y < tree_height; y++)
	{
		trunk_block->set_type(block_type::wood);

		delta = tree_height - y;
		if (delta <= 4)
		{
			if (delta == 4)
				delta = 3;

			for (int x = -delta; x <= delta; x++)
			for (int z = -delta; z <= delta; z++)
			{
				if (x == 0 && z == 0)
					continue;

				if (random({x, z + y}) > 0.1)
				{
					leave_block = trunk_block.get_neighbor({x, 0, z});
					validate_leave_block(leave_block);

					leave_block->set_type(block_type::leaves);
				}
			}
		}

		trunk_block = trunk_block.get_neighbor({0, 1, 0});
	}
}

void				tree_builder::validate_leave_block(const block_ptr &block)
{
	debug::check_critical
	(
		block != nullptr,
		"[game::tree_builder] Leave block is null"
	);
}