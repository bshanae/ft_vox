#pragma once

#include "game/world/block/block_type/block_meta_type/block_meta_type.h"

namespace			game
{
	enum class		block_type
	{
		air,
		stone,
		dirt,
		grass,
		sand,
		cloud,
		snow,
		dirt_with_grass,
		mushroom,
		water,
		blue_flower
	};

	block_meta_type	get_meta_type(block_type type);
}