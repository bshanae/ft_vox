#include "application.h"

#include "application/window.h"
#include "camera/camera.h"
#include "object/object.h"
#include "application/input.h"
				application::application()
{
	window::initialize();
	camera::initialize();
	//input::instance()->;
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
	camera::instance()->update();

	if (input::instance()->keys[GLFW_KEY_A] == input::key_state::PRESSED)
	{

	}
}
void			application::process_rendering()
{
	for (auto &object : objects)
		object->render();

	window::swap_buffers();
}