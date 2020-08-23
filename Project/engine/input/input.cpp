#include "input.h"

#include "engine/core/core.h"
#include "engine/window/window.h"

					input::input()
{
	for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_LAST; i++)
		keys[i] = key_state::waiting;
}

void				input::callback_key(GLFWwindow *window, int key, int code, int action, int mode)
{
	instance()->keys[key] = static_cast<key_state>(action);
}

void				input::reset_keys()
{
	for (auto &iterator : instance()->keys)
		if (iterator.second == key_state::pressed)
			iterator.second = key_state::held;
		else if (iterator.second == key_state::released)
			iterator.second = key_state::waiting;
}

void				input::update_mouse()
{
	static bool 	first_call = true;

	auto			instance = global<input>::instance();
	vec2 			position = window::mouse_position;

	if (first_call)
	{
		first_call = false;
		mouse_last_position = position;
		mouse_offset = ivec2(0);
	}
	else
		mouse_last_position = *mouse_current_position;

	mouse_current_position = position;
	mouse_offset.value.x = mouse_current_position->x - mouse_last_position->x;
	mouse_offset.value.y = mouse_last_position->y - mouse_current_position->y;
}