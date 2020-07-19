#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "common/OpenGL.h"
#include "application/application.h"
class input : public global<input>
{
	friend class	application;
	friend class	window;

 public:

	input();

	[[nodiscard]] static auto 			&get_keys()
	{
		return (instance()->keys);
	}
  enum class key_state : int
  {
	  DEFAULT = 0,
		  PRESSED = GLFW_PRESS,
		  RELEASED = GLFW_RELEASE,
		  HELD = GLFW_REPEAT
  };

private :

	static void 				glfw_callback_key(GLFWwindow *window, int key, int code, int action, int mode);

	static void 				glfw_callback_mouse_movement(GLFWwindow *window, double x, double y);
	static void 				glfw_callback_mouse_key(GLFWwindow *window, int key, int action, int mode);

	ivec2 mouse_offset =    ivec2 (0);
	ivec2 mouse_last_position =  ivec2 (-1, -1);
	ivec2 mouse_current_position   =  ivec2 (0);
	bool fist_mouse_move = true;


	map<int , key_state> keys;
	/*map
	{
		key_a -> prasdessed,
		key_b -> released
	}*/
};


