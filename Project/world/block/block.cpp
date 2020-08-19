#include "block.h"

block::face			block::from_axis_and_sign(axis axis, sign sign)
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

pair<axis, sign>	block::to_axis_and_sign(face face)
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

ostream					&operator << (ostream &stream, enum block::type type)
{
	switch (type)
	{
		case (block::type::air) :
			stream << "air";
			break ;

		case (block::type::dirt) :
			stream << "dirt";
			break ;

		case (block::type::dirt_with_grass) :
			stream << "dirt_with_grass";
			break ;

		case (block::type::water) :
			stream << "water";
			break ;
	}
	return (stream);
}