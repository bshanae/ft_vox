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

	bool						is_empty() const;

	bool						is_opaque() const;
	bool						is_transparent() const;
	bool						is_partially_transparent() const;
	bool						is_transparent_or_partially_transparent() const;

	bool						is_diagonal() const;

	bool						does_transmit_light() const;

	bool						is_solid() const;

	type						type;
	char						light_level = 0;
};

ostream							&operator << (ostream &stream, enum block::type type);