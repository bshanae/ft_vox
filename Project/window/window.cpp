#include "window.h"

#include <iostream>

					window::window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfw_window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
	assert(glfw_window != nullptr and "Can't initialize window");

	glfwMakeContextCurrent(glfw_window);
	glfwSwapInterval(1);

	glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(glfw_window, GLFW_STICKY_KEYS,GLFW_TRUE);

	bool			glad_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	assert(glad_status and "Can't initialize window");
}

					window::~window()
{
	glfwDestroyWindow(glfw_window);
	glfwTerminate();
}