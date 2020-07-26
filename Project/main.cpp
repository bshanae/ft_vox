#include "application/application.h"
#include "map/map.h"

#include "application/window.h"
#include "camera/camera.h"
#include "renderer/renderer.h"
#include "generation/generator_controller.h"

int						main()
{
	application::initialize();

	renderer::initialize();
	generator_controller::initialize();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	camera::create();
	map::create();

	application::execute();
	return (0);
}
