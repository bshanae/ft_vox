#include "application/application.h"
#include "map/map.h"

#include "camera/camera.h"
#include "renderer/renderer.h"
#include "generation/generator_controller.h"

int						main()
{
	application::initialize();

	renderer::initialize();
	generator_controller::initialize();

	camera::create();
	map::create();

	application::execute();
	return (0);
}
