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

	static face				from_axis_and_sign(axis axis, sign sign)
	{
		if (axis == axis::x and sign == sign::minus)
			 return (face::left);
		if (axis == axis::x and sign == sign::plus)
			 return (face::right);
		if (axis == axis::z and sign == sign::plus)
			 return (face::front);
		if (axis == axis::z and sign == sign::minus)
			 return (face::back);
		if (axis == axis::y and sign == sign::plus)
			 return (face::upper);
		if (axis == axis::y and sign == sign::minus)
			 return (face::bottom);
		assert(0);
	}

	static pair<axis, sign>	to_axis_and_sign(face face)
	{
		switch (face)
		{
			case (face::left) :
				return {axis::x, sign::minus};

			case (face::right) :
				return {axis::x, sign::plus};

			case (face::front) :
				return {axis::z, sign::plus};

			case (face::back) :
				return {axis::z, sign::minus};

			case (face::upper) :
				return {axis::y, sign::plus};

			case (face::bottom) :
				return {axis::y, sign::minus};
		}
	}

	explicit				block(enum type type = type::air)
	{
		this->type = type;
	}

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
};