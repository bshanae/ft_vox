#pragma once

#include "common/opengl.h"
#include "common/glm.h"
#include "common/aliases.h"
#include "common/property.h"
#include "common/global.h"

class									window : public global<window>
{
public :
										window();
										~window() override;

	static inline string				title = "";
	static inline ivec2					size = ivec2(1280, 720);

	static void 						close();
	static bool							is_closed();

	static void 						swap_buffers();
	static void 						use_depth_test(bool state);

	static inline
	property<read_only, vec2, window>	mouse_position;

	static vec2							to_normal(const ivec2 &value);
	static ivec2						to_absolute(const vec2 &value);

private :

	GLFWwindow							*glfw_window = nullptr;

	static vec2							mouse_position_getter();
};
