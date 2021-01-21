#include "window.h"

#include "engine/main/system/input/input.h"

using namespace		engine;

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
	glfwSetKeyCallback(glfw_window, input::get_callback_for_keyboard());
	glfwSetMouseButtonCallback(glfw_window, input::get_callback_for_mouse());

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

					window::~window()
{
	glfwDestroyWindow(glfw_window);
	glfwTerminate();
}

vec2				window::get_mouse_position()
{
	double			x;
	double			y;

	glfwGetCursorPos(get_instance()->glfw_window, &x, &y);
	return (invert_y(vec2(x, y)));
}

bool				window::is_closed()
{
	return glfwWindowShouldClose(get_instance()->glfw_window);
}

void 				window::close()
{
	glfwSetWindowShouldClose(get_instance()->glfw_window, true);
}

void				window::swap_buffers()
{
	glfwSwapBuffers(get_instance()->glfw_window);
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

ivec2				window::invert_y(const vec2 &value)
{
	return {value.x, size.y - value.y};
}