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
	application::register_layout("main");
	application::register_layout("water");

	map::create();
	camera::create();

	texture_atlas::initialize("Project/resources/atlases/default.png");
	texture_atlas::association_for(block::type::dirt) = ivec2(2, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).left = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).right = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).front = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).back = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).top = ivec2(12, 3);
	texture_atlas::association_for(block::type::dirt_with_grass).bottom = ivec2(2, 15);
	texture_atlas::association_for(block::type::water) = ivec2(13, 3);

	renderer::initialize();
	generator_controller::initialize();
	loader::initialize("test.vox");

	application::execute();
	return (0);
}
