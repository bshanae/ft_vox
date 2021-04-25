#pragma once

#include "application/common/imports/std.h"
#include "application/common/imports/glm.h"

namespace				game
{
	class				height_interpolator;
}

class					game::height_interpolator
{
public :
						height_interpolator(const function<int(vec2)> &height_generator);
	int					operator () (const vec2 &initial_position) const;

private :

	function<int(vec2)>	height_generator;
};