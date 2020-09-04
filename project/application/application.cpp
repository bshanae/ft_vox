#include "application.h"

#include "engine/core/core.h"
#include "ui/font/font_library.h"
#include "ui/font/symbol_renderer.h"
#include "world/texture_atlas/texture_atlas.h"
#include "world/world/world.h"
#include "world/block/block_selector.h"
#include "world/block/block_selector_renderer.h"
#include "world/chunk/chunk_renderer.h"
#include "world/generator/generator.h"
#include "world/loader/loader.h"
#include "player/camera/camera.h"
#include "player/player/player.h"

					application::application()
{
	initialize_engine();
	initialize_ui();
	initialize_world();
	initialize_player();
}

void 				application::execute()
{
	core::execute();
}

void 				application::initialize_engine()
{
	core::initialize();

	core::register_layout("System", false);
	core::register_layout("Opaque", true);
	core::register_layout("Transparent", true);
	core::register_layout("UI", false);
}

void 				application::initialize_ui()
{
	font_library::create();
	symbol_renderer::create();
}

void 				application::initialize_world()
{
	generator::create();
	biome_collection::create();
	loader::create();
	block_selector::create();
	block_selector_renderer::create();
	chunk_renderer::create();
	world::create();

	initialize_texture_atlas();
}

void 				application::initialize_texture_atlas()
{
	texture_atlas::initialize("Project/resources/atlases/default.png");

	texture_atlas::association_for(block::type::stone) = ivec2(1, 15);

	texture_atlas::association_for(block::type::dirt) = ivec2(2, 15);

	texture_atlas::association_for(block::type::dirt_with_grass).left = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).right = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).front = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).back = ivec2(3, 15);
	texture_atlas::association_for(block::type::dirt_with_grass).top = ivec2(12, 3);
	texture_atlas::association_for(block::type::dirt_with_grass).bottom = ivec2(2, 15);

	texture_atlas::association_for(block::type::water) = ivec2(13, 3);

	texture_atlas::association_for(block::type::blue_flower) = ivec2(12, 15);
}

void				application::initialize_player()
{
	camera::create();
	player::create();
}