#include "window.h"

#include "application/input.h"

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

	glfwGetFramebufferSize(glfw_window, &size.x, &size.y);
	glViewport(0, 0, size.x, size.y);

	input::initialize();

	glfwSetKeyCallback(glfw_window, input::callback_key);
	glfwSetCursorPosCallback(glfw_window, input::callback_mouse);
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
