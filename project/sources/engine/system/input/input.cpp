#include "input.h"

#include "engine/system/window/window.h"
#include "engine/processor/processor.h"

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
	states[key::shift] = state::waiting;
	states[key::left] = state::waiting;
	states[key::up] = state::waiting;
	states[key::right] = state::waiting;
	states[key::down] = state::waiting;
	states[key::mouse_left] = state::waiting;
	states[key::mouse_right] = state::waiting;

	mouse_offset = vec2();
	last_mouse_position = vec2();
	current_mouse_position = vec2();
}

vec2				input::get_mouse_offset() const
{
	return mouse_offset;
}

vec2				input::get_last_mouse_position() const
{
	return last_mouse_position;
}

vec2				input::get_current_mouse_position() const
{
	return current_mouse_position;
}

bool				input::is_pressed(enum key key) const
{
	return get_state_for_key(key) == state::pressed;
}

bool				input::is_released(enum key key) const
{
	return get_state_for_key(key) == state::released;
}

bool				input::is_held(enum key key) const
{
	return get_state_for_key(key) == state::held;
}

bool				input::is_pressed_or_held(enum key key) const
{
	enum state		state;

	state = get_state_for_key(key);
	return state == state::pressed or state == state::held;
}

bool				input::did_mouse_move() const
{
	return mouse_offset.x != 0 or mouse_offset.y != 0;
}

input::state		input::get_state_for_key(enum key key) const
{
	const auto		iterator = states.find(key);

	assert(iterator != states.end());
	return iterator->second;
}

void				input::callback_for_keyboard(GLFWwindow *window, int key, int code, int action, int mode)
{
	if (auto iterator = get_instance()->states.find((input::key)key); iterator != get_instance()->states.end())
		iterator->second = (input::state)action;
}

void 				input::callback_for_mouse_click(GLFWwindow *window, int key, int action, int mode)
{
	if (auto iterator = get_instance()->states.find((input::key)key); iterator != get_instance()->states.end())
		iterator->second = (input::state)action;
}

void				input::reset_keys()
{
	for (auto &iterator : states)
		if (iterator.second == state::pressed)
			iterator.second = state::held;
		else if (iterator.second == state::released)
			iterator.second = state::waiting;
}

void				input::update_mouse()
{
	static bool 	first_call = true;

	vec2 			position = window::get_instance()->get_mouse_position();

	if (first_call)
	{
		first_call = false;
		last_mouse_position = position;
		mouse_offset = ivec2(0);
	}
	else
		last_mouse_position = current_mouse_position;

	current_mouse_position = position;
	mouse_offset.x = current_mouse_position.x - last_mouse_position.x;
	mouse_offset.y = current_mouse_position.y - last_mouse_position.y;
}