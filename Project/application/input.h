#pragma once

#include "common/aliases.h"
#include "common/property.h"
#include "common/global.h"
#include "common/OpenGL.h"
#include "application/application.h"

class									input : public global<input>
{
	friend class						application;
	friend class						window;

public :

	enum class							key_state : int
	{
		waiting = 0,
		pressed = GLFW_PRESS,
		released = GLFW_RELEASE,
		held = GLFW_REPEAT
	};
										input();

	[[nodiscard]] static bool			is_pressed(int key)
	{
		return (instance()->keys[key] == key_state::pressed);
	}

	[[nodiscard]] static bool			is_released(int key)
	{
		return (instance()->keys[key] == key_state::released);
	}

	[[nodiscard]] static bool			is_held(int key)
	{
		return (instance()->keys[key] == key_state::held);
	}

	[[nodiscard]] static bool			is_pressed_or_held(int key)
	{
		return (instance()->keys[key] == key_state::pressed or instance()->keys[key] == key_state::held);
	}

	static inline
	property<read_only, ivec2, input>	mouse_offset;
	static inline
	property<read_only, ivec2, input>	mouse_last_position;
	static inline
	property<read_only, ivec2, input>	mouse_current_position;

 private :

	map<int, key_state>			keys;

	static void 						callback_key(GLFWwindow *window, int key, int code, int action, int mode);

	static void							reset_keys();
	static void							update_mouse();
};