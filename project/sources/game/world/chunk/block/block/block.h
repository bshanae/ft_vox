#pragma once

#include "application/common/imports/std.h"

namespace						world
{
	enum class 					axis;
	enum class 					sign;

	class						chunk;
	class						world;

	class						block;
}

class							world::block
{
	friend class 				::world::chunk;
	friend class 				::world::world;

public :

	enum						type : char
	{
		air,
		stone,
		dirt,
		dirt_with_grass,
		water,
		blue_flower
	};

	enum						face : char
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

	explicit					block(enum type type = air) : type(type) {}

	bool						is_empty() const;

	bool						is_opaque() const;
	bool						is_transparent() const;
	bool						is_partially_transparent() const;
	bool						is_transparent_or_partially_transparent() const;
	bool						is_diagonal() const;
	bool						does_transmit_light() const;
	bool						is_solid() const;
	bool						is_editable() const;

	type						type;
	char						light_level = 0;
};

ostream							&operator << (ostream &stream, enum world::block::type type);