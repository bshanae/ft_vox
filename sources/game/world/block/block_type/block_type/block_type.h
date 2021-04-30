#pragma once

#include "game/world/block/block_type/block_meta_type/block_meta_type.h"

namespace			game
{
	enum class		block_type
	{
		// Empty
		air,

		// Solid
		stone,
		stone_with_snow,
		dirt,
		dirt_with_grass,
		sand,
		wood,
		leaves,
		cloud,

		// Transparent
		water,

		// Diagonal
		grass,
		mushroom,
		blue_flower
	};

	block_meta_type	get_meta_type(block_type type);
}