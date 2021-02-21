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
	float						get_light_level() const;

	void						set_type(block_type type);
	void						set_light_level(float light_level);

private :

	block_type					type;
	float						light_level;
};


inline game::block_type			game::block::get_type() const
{
	return type;
}

inline float					game::block::get_light_level() const
{
	return light_level;
}

inline void						game::block::set_type(block_type type)
{
	this->type = type;
}

inline void						game::block::set_light_level(float light_level)
{
	this->light_level = light_level;
}