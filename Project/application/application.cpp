#include "application.h"

#include "window.h"
#include "object/object.h"

				application::application()
{
	window::initialize();
}

void			application::execute()
{
	auto		instance = global<application>::instance();

	while (not window::should_close())
	{
		glfwPollEvents();

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

}
void			application::process_rendering()
{
	for (auto &object : objects)
		object->render();

	window::swap_buffers();
}