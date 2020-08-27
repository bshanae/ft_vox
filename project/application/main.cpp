#include "engine/core/core.h"
#include "world/block/texture_atlas.h"
#include "world/world/world.h"
#include "world/block/block_selector.h"
#include "world/block/block_selector_renderer.h"
#include "world/chunk/chunk_renderer.h"
#include "world/generator/generator_controller.h"
#include "world/loader/loader.h"
#include "player/camera/camera.h"
#include "player/player/player.h"

int						main()
{
	core::initialize();

	core::register_layout("system");
	core::register_layout("first");
	core::register_layout("second");

	loader::create();
	block_selector_renderer::create();
	block_selector::create();
	chunk_renderer::create();
	world::create();

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

	texture_atlas::association_for(block::type::blue_flower) = ivec2(12, 15);

	core::execute();

	return (0);
}
