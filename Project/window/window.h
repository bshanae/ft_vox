#pragma once

#include <memory>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../Libraries/glm/glm/glm.hpp"

#include "../global.h"

class				window : public global<window>
{
	friend class 	application;

public :
					window();
					~window() override;

	static
	inline
	std::string		title = "";

	static
	inline
	glm::ivec2		size = glm::ivec2(1280, 720);

private :

	[[nodiscard]]
	bool 			should_close() const
	{
		return (glfwWindowShouldClose(glfw_window));
	}

	GLFWwindow		*glfw_window = nullptr;
};
