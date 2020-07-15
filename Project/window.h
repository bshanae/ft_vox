#pragma once

#include <memory>
#include <string>

#include "Libraries/glad/include/glad/glad.h"
#include "Libraries/glfw/include/GLFW/glfw3.h"
#include "Libraries/glm/glm/glm.hpp"

#include "global.h"

class				window : public global<window>
{
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

	GLFWwindow		*glfw_window = nullptr;
};
