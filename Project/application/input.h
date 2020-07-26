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

 private :

	vec2						mouse_offset = vec2(0.f);
	vec2						mouse_last_position = vec2(0.f);
	vec2						mouse_current_position = vec2(0.f);

	std::map<int, key_state>	keys;

	static void 				callback_key(GLFWwindow *window, int key, int code, int action, int mode);
	static void 				callback_mouse_key(GLFWwindow *window, int key, int action, int mode);

	void						reset_keys();
	void						update_mouse();
};


