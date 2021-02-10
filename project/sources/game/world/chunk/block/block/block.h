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
public :

	explicit					block(block_type type = block_type::air);
								~block() = default;

	friend ostream				&operator << (ostream &stream, enum game::block_type type);

	block_type					get_type() const;
	char						get_light_level() const;

	void						set_type(block_type type);
	void						set_light_level(char light_level);

private :

	block_type					type;
	char						light_level;
};