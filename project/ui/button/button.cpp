#include "button.h"

#include "engine/window/window.h"
#include "engine/input/input.h"
#include "ui/font/symbol.h"

					button::button()
{
	extends = ivec2(0);
}

void 				button::update()
{
	if (input::is_pressed(input::key::mouse_left) and
		is_inside(input::mouse_current_position) and
		*callback != nullptr)
		(*callback)();
}

bool				button::is_inside(const vec2 &point)
{
	const ivec2		min = *text::position - *extends;
	const ivec2		max = *text::position + *text::size + *extends;

	return
	(
		point.x > min.x and
		point.y > min.y and
		point.x < max.x and
		point.y < max.y
	);
}