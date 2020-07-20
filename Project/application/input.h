#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "common/OpenGL.h"
#include "application/application.h"
#include "camera/camera.h"

class							input : public global<input>
{
	friend class				application;
	friend class				window;

#warning "Remove this"
	friend class				camera;

public :

	enum class					key_state : int
	{
		waiting = 0,
		pressed = GLFW_PRESS,
		released = GLFW_RELEASE,
		held = GLFW_REPEAT
	};

								input();

	[[nodiscard]] static bool	is_pressed(int key)
	{
		return (instance()->keys[key] == key_state::pressed);
	}

	[[nodiscard]] static bool	is_released(int key)
	{
		return (instance()->keys[key] == key_state::released);
	}

	[[nodiscard]] static bool	is_held(int key)
	{
		return (instance()->keys[key] == key_state::held);
	}

	[[nodiscard]] static bool	is_pressed_or_held(int key)
	{
		return (instance()->keys[key] == key_state::pressed or instance()->keys[key] == key_state::held);
	}

	[[nodiscard]]
	static ivec2				get_mouse_offset()
	{
		return (instance()->mouse_offset);
	}

	[[nodiscard]]
	static ivec2				get_mouse_last_position()
	{
		return (instance()->mouse_last_position);
	}

	[[nodiscard]]
	static ivec2				get_mouse_current_position()
	{
		return (instance()->mouse_current_position);
	}

	[[deprecated]]
	void						set_mouse_offset(const ivec2 &value)
	{
		mouse_offset = value;
	}

 private :

	ivec2						mouse_offset = ivec2 (0);
	ivec2						mouse_last_position = ivec2 (-1, -1);
	ivec2						mouse_current_position = ivec2 (0);

	map<int, key_state>			keys;

	static void 				callback_key(GLFWwindow *window, int key, int code, int action, int mode);
	static void 				callback_mouse(GLFWwindow *window, double x, double y);
	static void 				callback_mouse_key(GLFWwindow *window, int key, int action, int mode);
};


