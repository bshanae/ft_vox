#include "window_tools.h"

#include "engine/main/system/window/window/window.h"

using namespace		engine;

vec2				window_tools::to_normal(const ivec2 &value)
{
	const ivec2		size = window::get_size();

	return {value.x / size.x, value.y / size.y};
}

ivec2				window_tools::to_absolute(const vec2 &value)
{
	const ivec2		size = window::get_size();

	return {value.x * size.x, value.y * size.y};
}

ivec2				window_tools::invert_y(const vec2 &value)
{
	return {value.x, window::get_size().y - value.y};
}