#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/global.h"

class						window : public global<window>
{
	friend class 			application;


 public :
							window();
							~window() override;

	static inline string	title = "";
	static inline ivec2		size = ivec2(1280, 720);
private :

	[[nodiscard]]
	static bool 			should_close();
	static void 			swap_buffers();

	GLFWwindow				*glfw_window = nullptr;
};
