#pragma once

#include "common/OpenGL.h"
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

	[[nodiscard]]
	static bool 						closed();
	static void 						close();

	static void 						swap_buffers();

	static inline
	property<read_only, vec2, window>	mouse_position;

private :

	GLFWwindow							*glfw_window = nullptr;

	static vec2							mouse_position_getter();
};
