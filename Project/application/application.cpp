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

	do
	{
		instance->process_input();

		if (window::closed())
			for (auto &object : instance->objects)
				object->destroy();

		instance->process_creating();
		instance->process_destroying();
		instance->process_updating();
		instance->process_rendering();
	}  while (not window::closed());
}

void			application::process_input()
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

void			application::process_creating()
{
	objects.insert(objects.end(), new_objects.begin(), new_objects.end());
	new_objects.clear();

	for (auto &object : objects)
	{
		if (object->state == object::state::just_created)
		{
			object->start();
			object->state = object::state::normal;
		}
	}
}

void			application::process_destroying()
{
	for (auto iterator = objects.begin(); iterator != objects.end(); )
		if ((*iterator)->state == object::state::should_be_destroyed)
		{
			(*iterator)->finish();
			iterator = objects.erase(iterator);
		}
		else
			++iterator;
}

void			application::process_updating()
{
	for (auto &object : objects)
		object->update();
}

void			application::process_rendering()
{
	auto 		&background = application_settings::background;

	glClearColor(background.x, background.y, background.z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	for (auto &object : objects)
		object->render();

	window::swap_buffers();
}