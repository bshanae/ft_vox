#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/global.h"

class				window : public global<window>
{
	friend class 	application;

public :
					window();
					~window() override;

	static
	inline
	string			title = "";

	static
	inline
	ivec2			size = ivec2(1280, 720);

private :

	[[nodiscard]]
	bool 			should_close() const
	{
		return (glfwWindowShouldClose(glfw_window));
	}

	GLFWwindow		*glfw_window = nullptr;
};
