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

	glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(glfw_window, input::callback_key);

#warning "Why it doesn't work?"
//	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
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

vec2				window::get_mouse_position()
{
	double			x;
	double			y;

	glfwGetCursorPos(instance()->glfw_window, &x, &y);
	return {x, y};
}