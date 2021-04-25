#include "block_face.h"

#include "application/common/debug/debug.h"

using namespace				game;

const vector<block_face>	&game::get_all_block_faces()
{
	static const
	vector<block_face>		faces =
	{
		block_face::left,
		block_face::right,
		block_face::front,
		block_face::back,
		block_face::top,
		block_face::bottom
	};

	return faces;
}

block_face					game::from_axis_and_sign(axis axis, sign sign)
{
	if (axis == axis::x and sign == sign::minus)
		return block_face::left;
	if (axis == axis::x and sign == sign::plus)
		return block_face::right;
	if (axis == axis::z and sign == sign::plus)
		return block_face::front;
	if (axis == axis::z and sign == sign::minus)
		return block_face::back;
	if (axis == axis::y and sign == sign::plus)
		return block_face::top;
	if (axis == axis::y and sign == sign::minus)
		return block_face::bottom;

	debug::raise_warning("[block] Can't translate face from axis and sign");
	return block_face::left;
}

pair<axis, sign>			game::to_axis_and_sign(block_face face)
{
	switch (face)
	{
		case block_face::left :
			return {axis::x, sign::minus};

		case block_face::right :
			return {axis::x, sign::plus};

		case block_face::front :
			return {axis::z, sign::plus};

		case block_face::back :
			return {axis::z, sign::minus};

		case block_face::top :
			return {axis::y, sign::plus};

		case block_face::bottom :
			return {axis::y, sign::minus};
	}
}