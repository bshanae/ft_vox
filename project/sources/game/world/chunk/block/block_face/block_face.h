#pragma once

#include "application/common/imports/std.h"

#include "game/world/tools/axis/axis.h"
#include "game/world/tools/sign/sign.h"

namespace				game
{
	enum class			block_face
	{
		left,
		right,
		front,
		back,
		top,
		bottom
	};

	block_face			from_axis_and_sign(axis axis, sign sign);
	pair<axis, sign>	to_axis_and_sign(block_face face);
}

