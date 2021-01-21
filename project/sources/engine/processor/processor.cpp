#include "processor.h"

#include "engine/core/object/object_manipulator/object_manipulator.h"
#include "engine/core/object/object_storage/object_storage/object_storage.h"
#include "engine/system/window/window.h"
#include "engine/system/input/input.h"
#include "engine/system/time/timer/timer.h"
#include "engine/rendering/main/layout/layout/layout.h"
#include "engine/rendering/main/layout/layout_manager/layout_manager.h"
#include "engine/processor/processor_settings.h"

using namespace	engine;

				processor::processor()
{
	window::construct();
	input::construct();
}

void			processor::execute()
{
	do
	{
		process_input();
		process_activation();
		process_updating();
		process_rendering();
	}
	while (not window::get_instance()->is_closed());
}

void			processor::process_input()
{
	static bool	empty_polygons = false;

	input::get_instance()->reset_keys();
	input::get_instance()->update_mouse();

	glfwPollEvents();

	if (input::get_instance()->is_pressed(input::key::escape))
		window::get_instance()->close();
	if (input::get_instance()->is_pressed(input::key::letter_p))
	{
		empty_polygons = not empty_polygons;
		glPolygonMode(GL_FRONT_AND_BACK, empty_polygons ? GL_LINE : GL_FILL);
	}
}

void			processor::process_activation()
{
	for (const auto &layout : layout_manager::get_layouts())
	for (auto &object : layout->get_objects())
	{
		if (object->get_state() == object::state::initialized)
			object->activate();
	}
}

void			processor::process_updating()
{
	for (const auto &layout : layout_manager::get_layouts())
	for (auto &object : layout->get_objects())
	{
		if (object->get_state() == object::state::activated)
			object->update();
	}
}

void			processor::process_rendering()
{
	auto 		&background = core_settings::background;

	glClearColor(background.x, background.y, background.z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	for (const auto &layout : layout_manager::get_layouts())
	{
		window::get_instance()->use_depth_test((layout->get_options() & (int)layout::use_depth_test) != 0);

		for (auto &object : layout->get_objects())
		{
			if (object->get_state() == object::state::activated)
				object->render();
		}
	}

	window::get_instance()->swap_buffers();
}