#include "block.h"

#include "game/world/utils/array3/array3.h"

using namespace		game;

block::face			block::from_axis_and_sign(axis axis, sign sign)
{
	if (axis == axis::x and sign == sign::minus)
		 return face::left;
	if (axis == axis::x and sign == sign::plus)
		 return face::right;
	if (axis == axis::z and sign == sign::plus)
		 return face::front;
	if (axis == axis::z and sign == sign::minus)
		 return face::back;
	if (axis == axis::y and sign == sign::plus)
		 return face::top;
	if (axis == axis::y and sign == sign::minus)
		 return face::bottom;
	assert(0);
}

pair<axis, sign>	block::to_axis_and_sign(face face)
{
	switch (face)
	{
		case face::left :
			return {axis::x, sign::minus};

		case face::right :
			return {axis::x, sign::plus};

		case face::front :
			return {axis::z, sign::plus};

		case face::back :
			return {axis::z, sign::minus};

		case face::top :
			return {axis::y, sign::plus};

		case face::bottom :
			return {axis::y, sign::minus};
	}
}

bool				block::is_empty() const
{
	return type == air;
}

bool				block::is_opaque() const
{
	return
	(
		type == stone or
		type == dirt or
		type == dirt_with_grass
	);
}

bool				block::is_transparent() const
{
	return type == water;
}

bool				block::is_partially_transparent() const
{
	return type == blue_flower;
}

bool				block::is_transparent_or_partially_transparent() const
{
	return is_transparent() or is_partially_transparent();
}

bool				block::is_diagonal() const
{
	return type == blue_flower;
}

bool				block::does_transmit_light() const
{
	return is_empty() or is_transparent() or is_partially_transparent();
}

bool				block::is_solid() const
{
	return is_opaque();
}

bool				block::is_editable() const
{
	return
	(
		type == stone or
		type == dirt or
		type == dirt_with_grass or
		type == blue_flower
	);
}

ostream				&operator << (ostream &stream, enum block::type type)
{
	switch (type)
	{
		case block::air :
			stream << "air";
			break ;

		case block::dirt :
			stream << "dirt";
			break ;

		case block::dirt_with_grass :
			stream << "dirt_with_grass";
			break ;

		case block::water :
			stream << "water";
			break ;

		case block::blue_flower :
			stream << "blue_flower";
			break ;

		default :
			break ;
	}
	return (stream);
}