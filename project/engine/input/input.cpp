#include "input.h"

#include "engine/core/core.h"
#include "engine/window/window.h"

using namespace		engine;

					input::input()
{
	states[key::letter_a] = state::waiting;
	states[key::letter_b] = state::waiting;
	states[key::letter_c] = state::waiting;
	states[key::letter_d] = state::waiting;
	states[key::letter_e] = state::waiting;
	states[key::letter_f] = state::waiting;
	states[key::letter_g] = state::waiting;
	states[key::letter_h] = state::waiting;
	states[key::letter_i] = state::waiting;
	states[key::letter_j] = state::waiting;
	states[key::letter_k] = state::waiting;
	states[key::letter_l] = state::waiting;
	states[key::letter_m] = state::waiting;
	states[key::letter_n] = state::waiting;
	states[key::letter_o] = state::waiting;
	states[key::letter_p] = state::waiting;
	states[key::letter_q] = state::waiting;
	states[key::letter_r] = state::waiting;
	states[key::letter_s] = state::waiting;
	states[key::letter_t] = state::waiting;
	states[key::letter_u] = state::waiting;
	states[key::letter_v] = state::waiting;
	states[key::letter_w] = state::waiting;
	states[key::letter_x] = state::waiting;
	states[key::letter_y] = state::waiting;
	states[key::letter_z] = state::waiting;
	states[key::number_1] = state::waiting;
	states[key::number_2] = state::waiting;
	states[key::number_3] = state::waiting;
	states[key::number_4] = state::waiting;
	states[key::number_5] = state::waiting;
	states[key::number_6] = state::waiting;
	states[key::number_7] = state::waiting;
	states[key::number_8] = state::waiting;
	states[key::number_9] = state::waiting;
	states[key::number_0] = state::waiting;
	states[key::escape] = state::waiting;
	states[key::enter] = state::waiting;
	states[key::space] = state::waiting;
	states[key::left] = state::waiting;
	states[key::up] = state::waiting;
	states[key::right] = state::waiting;
	states[key::down] = state::waiting;
	states[key::mouse_left] = state::waiting;
	states[key::mouse_right] = state::waiting;
}

bool				input::is_pressed(enum key key)
{
	assert(instance()->states.find(key) != instance()->states.end());
	return (instance()->states[key] == state::pressed);
}

bool				input::is_released(enum key key)
{
	assert(instance()->states.find(key) != instance()->states.end());
	return (instance()->states[key] == state::released);
}

bool				input::is_held(enum key key)
{
	assert(instance()->states.find(key) != instance()->states.end());
	return (instance()->states[key] == state::held);
}

bool				input::is_pressed_or_held(enum key key)
{
	assert(instance()->states.find(key) != instance()->states.end());
	return (instance()->states[key] == state::pressed or instance()->states[key] == state::held);
}

bool				input::have_mouse_moved()
{
	return (mouse_offset->x != 0 or mouse_offset->y != 0);
}

void				input::callback_for_keyboard(GLFWwindow *window, int key, int code, int action, int mode)
{
	if (auto iterator = instance()->states.find((input::key)key); iterator != instance()->states.end())
		iterator->second = (input::state)action;
}

void 				input::callback_for_mouse_click(GLFWwindow *window, int key, int action, int mode)
{
	if (auto iterator = instance()->states.find((input::key)key); iterator != instance()->states.end())
		iterator->second = (input::state)action;
}

void				input::reset_keys()
{
	for (auto &iterator : instance()->states)
		if (iterator.second == state::pressed)
			iterator.second = state::held;
		else if (iterator.second == state::released)
			iterator.second = state::waiting;
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
	mouse_offset.value.y = mouse_current_position->y - mouse_last_position->y;
}