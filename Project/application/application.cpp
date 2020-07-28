#include "application.h"

#include "application/window.h"
#include "application/input.h"

				application::application()
{
	window::initialize();
	input::initialize();
}

void			application::execute()
{
	auto		instance = global<application>::instance();

	while (not window::closed())
	{
		instance->process_input();
		instance->process_early_updating();
		instance->process_creating();
		instance->process_destroying();
		instance->process_updating();
		instance->process_rendering();
	}
}

void			application::process_input()
{

}

void			application::process_creating()
{
	static bool	empty_polygons = false;

	input::instance()->reset_keys();
	input::instance()->update_mouse();

	glfwPollEvents();

	if (input::is_pressed(GLFW_KEY_ESCAPE))
		window::close();
	if (input::is_pressed(GLFW_KEY_P))
	{
		empty_polygons = not empty_polygons;
		glPolygonMode(GL_FRONT_AND_BACK, empty_polygons ? GL_LINE : GL_FILL);
	}
}

void			application::process_destroying()
{

}

void			application::process_early_updating()
{
	auto 		copy = objects;

	for (auto &object : copy)
		object->early_update();
}

void			application::process_updating()
{
	for (auto &object : objects)
		object->update();
}

void			application::process_rendering()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	for (auto &object : objects)
		object->render();

	window::swap_buffers();
}