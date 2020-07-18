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

	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) and "Can't initialize window");

	int 			width;
	int 			height;

	glfwGetFramebufferSize(glfw_window, &width, &height);
	glViewport(0, 0, width, height);

//	glfwSwapInterval(1);

//	glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(glfw_window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

					window::~window()
{
	glfwDestroyWindow(glfw_window);
	glfwTerminate();
}

bool				window::should_close()
{
	return (glfwWindowShouldClose(instance()->glfw_window));
}

void				window::swap_buffers()
{
	glfwSwapBuffers(instance()->glfw_window);
}