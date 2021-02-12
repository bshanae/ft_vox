#pragma once

#include "application/common/templates/singleton/singleton.h"
#include "application/common/imports/opengl.h"
#include "application/common/imports/glm.h"
#include "application/common/imports/std.h"

namespace					engine
{
	class					window;
}

class						engine::window : public singleton<window>
{
public :

	static inline string	title = "";
	static inline ivec2		size = ivec2(1280, 720);

							window();
							~window() override;
public :

	static vec2				get_mouse_position();

	static bool				is_closed();
	static void 			close();

	static void 			swap_buffers();

	static void 			use_depth_test(bool state);

	static vec2				to_normal(const ivec2 &value);
	static ivec2			to_absolute(const vec2 &value);
	static ivec2			invert_y(const vec2 &value);

private :

	GLFWwindow				*glfw_window = nullptr;
};
