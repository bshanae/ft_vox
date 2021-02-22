#pragma once

#include "application/common/imports/glm.h"

namespace			engine
{
	class 			window_tools;
}

class				engine::window_tools
{
public :

	static vec2		to_normal(const ivec2 &value);
	static ivec2	to_absolute(const vec2 &value);
	static ivec2	invert_y(const vec2 &value);
};


