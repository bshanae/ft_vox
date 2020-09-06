#pragma once

#include "common/opengl.h"
#include "common/glm.h"
#include "common/aliases.h"
#include "common/property.h"
#include "common/global.h"

namespace								engine
{
	class								core;
	class								window;

	class								input;
}

class									engine::input : public global<input>
{
	friend class						engine::core;
	friend class						engine::window;

public :

	enum class							key : int
	{
		letter_a = GLFW_KEY_A,
		letter_b = GLFW_KEY_B,
		letter_c = GLFW_KEY_C,
		letter_d = GLFW_KEY_D,
		letter_e = GLFW_KEY_E,
		letter_f = GLFW_KEY_F,
		letter_g = GLFW_KEY_G,
		letter_h = GLFW_KEY_H,
		letter_i = GLFW_KEY_I,
		letter_j = GLFW_KEY_J,
		letter_k = GLFW_KEY_K,
		letter_l = GLFW_KEY_L,
		letter_m = GLFW_KEY_M,
		letter_n = GLFW_KEY_N,
		letter_o = GLFW_KEY_O,
		letter_p = GLFW_KEY_P,
		letter_q = GLFW_KEY_Q,
		letter_r = GLFW_KEY_R,
		letter_s = GLFW_KEY_S,
		letter_t = GLFW_KEY_T,
		letter_u = GLFW_KEY_U,
		letter_v = GLFW_KEY_V,
		letter_w = GLFW_KEY_W,
		letter_x = GLFW_KEY_X,
		letter_y = GLFW_KEY_Y,
		letter_z = GLFW_KEY_Z,
		number_1 = GLFW_KEY_1,
		number_2 = GLFW_KEY_2,
		number_3 = GLFW_KEY_3,
		number_4 = GLFW_KEY_4,
		number_5 = GLFW_KEY_5,
		number_6 = GLFW_KEY_6,
		number_7 = GLFW_KEY_7,
		number_8 = GLFW_KEY_8,
		number_9 = GLFW_KEY_9,
		number_0 = GLFW_KEY_0,
		escape = GLFW_KEY_ESCAPE,
		enter = GLFW_KEY_ENTER,
		space = GLFW_KEY_SPACE,
		shift = GLFW_KEY_LEFT_SHIFT,
		left = GLFW_KEY_LEFT,
		up = GLFW_KEY_UP,
		right = GLFW_KEY_RIGHT,
		down = GLFW_KEY_DOWN,
		mouse_left = GLFW_MOUSE_BUTTON_LEFT,
		mouse_right = GLFW_MOUSE_BUTTON_RIGHT,
	};

	enum class							state : int
	{
		waiting = 0,
		pressed = GLFW_PRESS,
		released = GLFW_RELEASE,
		held = GLFW_REPEAT
	};

										input();

	static bool							is_pressed(enum key key);
	static bool							is_released(enum key key);
	static bool							is_held(enum key key);
	static bool							is_pressed_or_held(enum key key);

	static bool							have_mouse_moved();

	static inline
	property<read_only, vec2, input>	mouse_offset;
	static inline
	property<read_only, vec2, input>	mouse_last_position;
	static inline
	property<read_only, vec2, input>	mouse_current_position;

 private :

	unordered_map<key, state>			states;

	static void 						callback_for_keyboard(GLFWwindow *window, int key, int code, int action, int mode);
	static void 						callback_for_mouse_click(GLFWwindow *window, int key, int action, int mode);

	static void							reset_keys();
	static void							update_mouse();
};