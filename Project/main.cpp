#include "application/application.h"
#include "map/map.h"
#include "map/texture_atlas.h"
#include "camera/camera.h"
#include "renderer/renderer.h"
#include "generator/generator_controller.h"
#include "loader/loader.h"

int						main()
{
	application::initialize();

	texture_atlas::initialize("Project/resources/atlases/default.png");
	texture_atlas::associate_texture_with_block(block::type::dirt, ivec2(2, 15));
	texture_atlas::associate_texture_with_block(block::type::stone, ivec2(1, 15));

	renderer::initialize();
	generator_controller::initialize();
	loader::initialize("test.vox");

	camera::create();
	map::create();

	application::execute();
	return (0);
}
