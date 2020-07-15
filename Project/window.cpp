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
	if (not glfw_window)
	{
#warning "Add error"
		std::terminate();
	}

	glfwMakeContextCurrent(glfw_window);
//	glfwSetFramebufferSizeCallback(glfw_window, Events::framebuffer_size_callback);
//	glfwSetCursorPosCallback(glfw_window, Events::mouse_callback);
//	glfwSetScrollCallback(glfw_window, Events::scroll_callback);
	glfwSwapInterval(1);

	glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(glfw_window, GLFW_STICKY_KEYS,GLFW_TRUE);

	if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
#warning "Add error"
		std::terminate();
	}

//	GLint flags;
//	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
//	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
//	{
//		glEnable(GL_DEBUG_OUTPUT);
//		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
//		//glDebugMessageCallback(glDebugOutput, nullptr);
//		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
//	}
}

					window::~window()
{
	glfwDestroyWindow(glfw_window);
	glfwTerminate();
}