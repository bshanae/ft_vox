#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "common/OpenGL.h"

class input : public global<input>
{
	friend class	window;
public:

	input()
	{
		for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_LAST; i++)
			keys[i] = key_state::DEFAULT;
	}

private :

	static void 				glfw_callback_key(GLFWwindow *window, int key, int code, int action, int mode)
	{
		auto					instance = global<input>::instance();

		if (instance->keys[key] == key_state::RELEASED and action == GLFW_RELEASE)
			instance->keys[key] = key_state::DEFAULT;
		else
			instance->keys[key] = static_cast<key_state>(action);
	}

	static void 				glfw_callback_mouse_movement(GLFWwindow *window, double x, double y);
	static void 				glfw_callback_mouse_key(GLFWwindow *window, int key, int action, int mode);

	ivec2 mouse_offset =    ivec2 (0);
	ivec2 mouse_last_position =  ivec2 (0);
	ivec2 mouse_current_position   =  ivec2 (0);

	enum class key_state : int
	{
		DEFAULT = 0,
		PRESSED = GLFW_PRESS,
		RELEASED = GLFW_RELEASE,
		HELD = GLFW_REPEAT
	};

	map<int , key_state> keys;

	/*map
	{
		key_a -> prasdessed,
		key_b -> released
	}*/
};


