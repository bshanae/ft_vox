#pragma once

#include "game/world/chunk/block/block_type/block_type/block_type.h"

#include "application/common/imports/std.h"

namespace						game
{
	enum class 					axis;
	enum class 					sign;

	class						chunk;
	class						world;

	class						block;
}

class							game::block
{
	friend class 				chunk;
	friend class 				world;

public :

	explicit					block(block_type type = block_type::air);
								~block() = default;

	friend ostream				&operator << (ostream &stream, enum game::block_type type);

	block_type					type;
	char						light_level = 0;
};