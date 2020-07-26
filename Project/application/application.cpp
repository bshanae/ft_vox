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

	while (not window::should_close())
	{
		glfwPollEvents();
		input::instance()->update_mouse_data();

		if (input::is_pressed(GLFW_KEY_ESCAPE))
			break ;

		instance->process_creating();
		instance->process_destroying();
		instance->process_updating();
		instance->process_rendering();
	}
}

void			application::process_creating()
{

}

void			application::process_destroying()
{

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