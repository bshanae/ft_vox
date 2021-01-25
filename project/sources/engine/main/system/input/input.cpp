#include "input.h"

#include "engine/main/system/window/window.h"
#include "engine/main/processor/processor.h"

#include "application/common/debug/debug.h"

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

vec2				input::get_mouse_offset()
{
	return get_instance()->mouse_offset;
}

vec2				input::get_last_mouse_position()
{
	return get_instance()->last_mouse_position;
}

vec2				input::get_current_mouse_position()
{
	return get_instance()->current_mouse_position;
}

bool				input::is_pressed(enum key key)
{
	return get_instance()->get_state_for_key(key) == state::pressed;
}

bool				input::is_released(enum key key)
{
	return get_instance()->get_state_for_key(key) == state::released;
}

bool				input::is_held(enum key key)
{
	return get_instance()->get_state_for_key(key) == state::held;
}

bool				input::is_pressed_or_held(enum key key)
{
	enum state		state;

	state = get_instance()->get_state_for_key(key);
	return state == state::pressed or state == state::held;
}

bool				input::did_mouse_move()
{
	auto			instance = get_instance();

	return instance->mouse_offset.x != 0 or instance->mouse_offset.y != 0;
}

void				input::reset_keys()
{
	for (auto &iterator : get_instance()->states)
		if (iterator.second == state::pressed)
			iterator.second = state::held;
		else if (iterator.second == state::released)
			iterator.second = state::waiting;
}

void				input::update_mouse()
{
	const auto 		instance = get_instance();
	static bool 	first_call = true;

	vec2 			position = window::get_mouse_position();

	if (first_call)
	{
		first_call = false;
		instance->last_mouse_position = position;
		instance->mouse_offset = ivec2(0);
	}
	else
		instance->last_mouse_position = instance->current_mouse_position;

	instance->current_mouse_position = position;
	instance->mouse_offset.x = instance->current_mouse_position.x - instance->last_mouse_position.x;
	instance->mouse_offset.y = instance->current_mouse_position.y - instance->last_mouse_position.y;
}

input::state		input::get_state_for_key(enum key key) const
{
	const auto		iterator = states.find(key);

	debug::check_critical(iterator != states.end(), "[engine::input] Can't find a key");
	return iterator->second;
}

void				input::callback_for_keyboard(GLFWwindow *window, int key, int code, int action, int mode)
{
	if (auto iterator = get_instance()->states.find((input::key)key); iterator != get_instance()->states.end())
		iterator->second = (input::state)action;
}

void 				input::callback_for_mouse(GLFWwindow *window, int key, int action, int mode)
{
	if (auto iterator = get_instance()->states.find((input::key)key); iterator != get_instance()->states.end())
		iterator->second = (input::state)action;
}