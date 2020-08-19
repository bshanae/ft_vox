#include "core.h"

#include "core/core/core_settings.h"
#include "core/window/window.h"
#include "core/input/input.h"
#include "core/time/timer.h"

				core::core()
{
	window::initialize();
	input::initialize();
}

void			core::register_layout(const string &key)
{
	instance()->layouts[key] = {};
}

void			core::execute()
{
	auto		instance = global<core>::instance();

	do
	{
		instance->process_input();

		if (window::is_closed())
			for (auto &layout : instance->layouts)
				for (auto &object : layout.second)
					object->destroy();

		instance->process_creating();
		instance->process_destroying();
		instance->process_updating();
		instance->process_rendering();
	}  while (not window::is_closed());
}

void			core::process_input()
{
	static bool	empty_polygons = false;

	input::reset_keys();
	input::update_mouse();

	glfwPollEvents();

	if (input::is_pressed(GLFW_KEY_ESCAPE))
		window::close();
	if (input::is_pressed(GLFW_KEY_P))
	{
		empty_polygons = not empty_polygons;
		glPolygonMode(GL_FRONT_AND_BACK, empty_polygons ? GL_LINE : GL_FILL);
	}
}

void			core::process_creating()
{
	for (auto &new_object : new_objects)
		if (auto iterator = layouts.find(new_object.first); iterator != layouts.end())
			iterator->second.push_back(new_object.second);
		else
			assert(false and "Unknown layout");

	for (auto &layout : layouts)
		for (auto &object : layout.second)
			if (object->state == object::state::uninitialized)
				object->initialize();

	new_objects.clear();
}

void			core::process_destroying()
{
	for (auto &layout : layouts)
		for (auto iterator = layout.second.begin(); iterator != layout.second.end();)
			if ((*iterator)->should_be_destroyed)
			{
				(*iterator)->deinitialize();
				iterator = layout.second.erase(iterator);
			}
			else
				++iterator;
}

void			core::process_updating()
{
	for (auto &layout : layouts)
		for (auto &object : layout.second)
			if (object->should_be_updated and object->state == object::state::active)
				object->update();
}

void			core::process_rendering()
{
	auto 		&background = core_settings::background;

	glClearColor(background.x, background.y, background.z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	for (auto &layout : layouts)
		for (auto &object : layout.second)
			if (object->should_be_rendered and object->state == object::state::active)
				object->render();

	window::swap_buffers();
}