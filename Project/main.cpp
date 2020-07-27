#include "application/application.h"
#include "map/map.h"
#include "camera/camera.h"
#include "renderer/renderer.h"
#include "generation/generator_controller.h"

#include "map/texture.h"

int						main()
{
	application::initialize();

	renderer::initialize();
	generator_controller::initialize();

	texture				t = texture("/Users/v.belchenko/Desktop/E2a0zsi.png");

	t.use(true);

	camera::create();
	map::create();

	application::execute();
	return (0);
}
