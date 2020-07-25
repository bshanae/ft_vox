#include "application.h"

#include "application/window.h"
#include "camera/camera.h"
#include "object/object.h"
#include "generation/generator_controller.h"

				application::application()
{
	window::initialize();
	camera::initialize();
	generator_controller::initialize();
	generator_controller::execute();



	std::array<std::array<float, 20>, 20> map;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			map[i][j] = generator_controller::instance()->get_generator(
				generator_controller::generator_type::plain)->get_noise(i,j);
		}
	}

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			std::cout << map[i][j] << " ";
		}
		std::cout << std::endl;
	}
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
}
void			application::process_rendering()
{
	for (auto &object : objects)
		object->render();

	window::swap_buffers();
}