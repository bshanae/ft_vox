#pragma once

#include "common/array3.h"

class							block
{
	friend class 				chunk;
	friend class 				world;

public :

	enum class					type : char
	{
		air,
		dirt,
		dirt_with_grass,
		water,
		blue_flower
	};

	enum class					face : char
	{
		left,
		right,
		front,
		back,
		top,
		bottom
	};

	static face					from_axis_and_sign(axis axis, sign sign);
	static pair<axis, sign>		to_axis_and_sign(face face);

	explicit					block(enum type type = type::air) : type(type) {}

	[[nodiscard]] bool			is_empty() const;
	[[nodiscard]] bool			is_opaque() const;
	[[nodiscard]] bool			is_transparent() const;
	[[nodiscard]] bool			is_partially_transparent() const;
	[[nodiscard]] bool			is_transparent_or_partially_transparent() const;
	[[nodiscard]] bool			is_diagonal() const;
	[[nodiscard]] bool			does_transmit_light() const;

	type						type;
	char						light_level = 0;
};

ostream							&operator << (ostream &stream, enum block::type type);