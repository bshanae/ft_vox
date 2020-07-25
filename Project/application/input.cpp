#include "input.h"

#include "application/window.h"

					input::input()
{
	for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_LAST; i++)
		keys[i] = key_state::waiting;
}

void				input::callback_key(GLFWwindow *window, int key, int code, int action, int mode)
{
	auto			instance = global<input>::instance();

	if (instance->keys[key] == key_state::pressed and action == GLFW_PRESS)
		instance->keys[key] = key_state::held;
  	else if (instance->keys[key] == key_state::released and action == GLFW_RELEASE)
  		instance->keys[key] = key_state::waiting;
  	else
  		instance->keys[key] = static_cast<key_state>(action);
}

void				input::update()
{
	static bool 	first_call = true;

	auto			instance = global<input>::instance();
	vec2 			position = window::get_mouse_position();

	if (first_call)
	{
		first_call = false;
		instance->mouse_last_position = position;
		instance->mouse_offset = ivec2(0);
	}
	else
		instance->mouse_last_position = instance->mouse_current_position;

	instance->mouse_current_position = position;
	instance->mouse_offset.x = instance->mouse_current_position.x - instance->mouse_last_position.x;
	instance->mouse_offset.y = instance->mouse_last_position.y - instance->mouse_current_position.y;
}