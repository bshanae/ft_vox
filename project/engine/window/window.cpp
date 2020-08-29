#include "window.h"

#include "engine/input/input.h"

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
	glfwSetKeyCallback(glfw_window, input::callback_for_keyboard);
	glfwSetMouseButtonCallback(glfw_window, input::callback_for_mouse_click);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mouse_position.getter = mouse_position_getter;
	mouse_position.prohibit_direct_access();
}

					window::~window()
{
	glfwDestroyWindow(glfw_window);
	glfwTerminate();
}

bool				window::is_closed()
{
	return (glfwWindowShouldClose(instance()->glfw_window));
}

void 				window::close()
{
	glfwSetWindowShouldClose(instance()->glfw_window, true);
}

void				window::swap_buffers()
{
	glfwSwapBuffers(instance()->glfw_window);
}

void				window::use_depth_test(bool state)
{
	if (state)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

vec2				window::to_normal(const ivec2 &value)
{
	return {value.x / size.x, value.y / size.y};
}

ivec2				window::to_absolute(const vec2 &value)
{
	return {value.x * size.x, value.y * size.y};
}

vec2				window::mouse_position_getter()
{
	double			x;
	double			y;

	glfwGetCursorPos(instance()->glfw_window, &x, &y);
	return {x, y};
}