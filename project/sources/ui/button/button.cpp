#include "button.h"

#include "engine/window/window.h"
#include "engine/input/input.h"
#include "ui/font/symbol/symbol.h"

using namespace		ui;
using namespace		engine;

					button::button()
{
	extends = ivec2(0);
}

void 				button::set_callback(const function<void(void)> &callback)
{
	this->callback = callback;
}

ivec2				button::get_extends() const
{
	return extends;
}

void 				button::update()
{
	if
	(
		input::get_instance()->is_pressed(input::key::mouse_left) and
		is_inside(input::get_instance()->get_current_mouse_position()) and
		callback != nullptr
	)
	{
		callback();
	}
}

bool				button::is_inside(const vec2 &point)
{
	const ivec2		min = get_position() - extends;
	const ivec2		max = get_position() + get_size() + extends;

	return
	(
		point.x > min.x and
		point.y > min.y and
		point.x < max.x and
		point.y < max.y
	);
}