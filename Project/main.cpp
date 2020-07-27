#include "application/application.h"
#include "map/map.h"
#include "map/texture_atlas.h"
#include "camera/camera.h"
#include "renderer/renderer.h"
#include "generation/generator_controller.h"

int						main()
{
	application::initialize();

	texture_atlas::initialize("Project/resources/atlases/default.png");

	texture_atlas::associate_texture_with_block(block::type::dirt, ivec2(2, 15));

	renderer::initialize();
	generator_controller::initialize();

	camera::create();
	map::create();

	application::execute();
	return (0);
}
