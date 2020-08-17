#include "application/application.h"
#include "world/block/texture_atlas.h"
#include "world/world/world.h"
#include "world/chunk/chunk_renderer.h"
#include "world/chunk/highlighter.h"
#include "world/chunk/highlighter_renderer.h"
#include "world/generator/generator_controller.h"
#include "world/loader/loader.h"
#include "player/camera/camera.h"
#include "player/player/player.h"

int						main()
{
	application::initialize();

	application::register_layout("system");
	application::register_layout("main");
	application::register_layout("water");

	world::create();
	highlighter::create();
	highlighter_renderer::create();
	camera::create();
	player::create();

	texture_atlas::initialize("Project/resources/atlases/default.png");
	texture_atlas::association_for(block::type::dirt) = ivec2(2, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).left = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).right = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).front = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).back = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).top = ivec2(12, 3);
	texture_atlas::association_for(block::type::dirt_with_grass).bottom = ivec2(2, 15);
	texture_atlas::association_for(block::type::water) = ivec2(13, 3);

	chunk_renderer::initialize();
	generator_controller::initialize();
	loader::initialize("test.vox");

	application::execute();
	return (0);
}
