#pragma once

#include "common/array3.h"

class						block
{
	friend class 			chunk;
	friend class 			world;

public :

	enum class				type : char
	{
		air,
		dirt,
		dirt_with_grass,
		water
	};

	enum class				face : char
	{
		left,
		right,
		front,
		back,
		upper,
		bottom
	};

	static face				from_axis_and_sign(axis axis, sign sign);
	static pair<axis, sign>	to_axis_and_sign(face face);

	explicit				block(enum type type = type::air) : type(type) {}

	[[nodiscard]]
	inline bool				is_empty() const
	{
		return (type == type::air);
	}

	[[nodiscard]]
	inline bool				is_transparent() const
	{
		return (type == type::water);
	}


	type					type;
	char					light_level = 0;

	int 					test = 2;
};

ostream						&operator << (ostream &stream, enum block::type type);