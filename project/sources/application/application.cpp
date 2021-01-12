#include "application.h"

#include "engine/core/core.h"
#include "ui/font/font_library/font_library.h"
#include "ui/font/symbol/symbol_renderer.h"
#include "world/texture_atlas/texture_atlas.h"
#include "world/world/world.h"
#include "world/block/block_selector/block_selector.h"
#include "world/block/block_selector/block_selector_renderer.h"
#include "world/chunk/chunk_renderer.h"
#include "world/generator/generator/generator.h"
#include "world/loader/loader/loader.h"
#include "player/camera/camera.h"
#include "player/player/player.h"

					application::application::application()
{
	initialize_engine();
	initialize_ui();
	initialize_world();
	initialize_player();
}

void 				application::application::execute()
{
	engine::core::execute();
}

void 				application::application::initialize_engine()
{
	engine::core::initialize();

	engine::core::register_layout("System", false);
	engine::core::register_layout("Opaque", true);
	engine::core::register_layout("Transparent", true);
	engine::core::register_layout("UI", false);
}

void 				application::application::initialize_ui()
{
	ui::font_library::create();
	ui::symbol_renderer::create();
}

void 				application::application::initialize_world()
{
	world::generator::create();
	world::biome_collection::create();
	world::loader::create();
	world::block_selector::create();
	world::block_selector_renderer::create();
	world::chunk_renderer::create();
	world::world::create();

	initialize_texture_atlas();
}

void 				application::application::initialize_texture_atlas()
{
	world::texture_atlas::initialize("project/resources/atlases/default.png");

	world::texture_atlas::association_for(world::block::stone) = ivec2(1, 15);

	world::texture_atlas::association_for(world::block::dirt) = ivec2(2, 15);

	world::texture_atlas::association_for(world::block::dirt_with_grass).left = ivec2(3, 15);
	world::texture_atlas::association_for(world::block::dirt_with_grass).right = ivec2(3, 15);
	world::texture_atlas::association_for(world::block::dirt_with_grass).front = ivec2(3, 15);
	world::texture_atlas::association_for(world::block::dirt_with_grass).back = ivec2(3, 15);
	world::texture_atlas::association_for(world::block::dirt_with_grass).top = ivec2(12, 3);
	world::texture_atlas::association_for(world::block::dirt_with_grass).bottom = ivec2(2, 15);

	world::texture_atlas::association_for(world::block::water) = ivec2(13, 3);

	world::texture_atlas::association_for(world::block::blue_flower) = ivec2(12, 15);
}

void				application::application::initialize_player()
{
	player::camera::create();
	player::player::create();
}