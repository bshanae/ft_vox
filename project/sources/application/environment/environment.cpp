#include "environment.h"

#include "engine/processor/processor.h"
#include "engine/rendering/ui/font/font_library/font_library.h"
#include "engine/rendering/ui/font/symbol/symbol_renderer.h"
#include "engine/rendering/main/camera/camera.h"

#include "game/world/utils/texture_atlas/texture_atlas.h"
#include "game/world/world/world.h"
#include "game/world/chunk/block/block_selector/block_selector/block_selector.h"
#include "game/world/chunk/block/block_selector/block_selector_renderer/block_selector_renderer.h"
#include "game/world/chunk/chunk/chunk_renderer/chunk_renderer.h"
#include "game/world/chunk/generator/generator/generator.h"
#include "game/player/player.h"

					application::application::application()
{
	initialize_engine();
	initialize_ui();
	initialize_game();
	initialize_player();
}

void 				application::application::execute()
{
	engine::processor::execute();
}

void 				application::application::initialize_engine()
{
	engine::processor::initialize();

	engine::processor::register_layout("System", false);
	engine::processor::register_layout("Opaque", true);
	engine::processor::register_layout("Transparent", true);
	engine::processor::register_layout("UI", false);
}

void 				application::application::initialize_ui()
{
	ui::font_library::create();
	ui::symbol_renderer::create();
}

void 				application::application::initialize_game()
{
	game::generator::create();
	game::biome_collection::create();
	game::block_selector::create();
	game::block_selector_renderer::create();
	game::chunk_renderer::create();
	game::world::create();

	initialize_texture_atlas();
}

void 				application::application::initialize_texture_atlas()
{
	game::texture_atlas::initialize("project/resources/atlases/default.png");

	game::texture_atlas::association_for(game::block::stone) = ivec2(1, 15);

	game::texture_atlas::association_for(game::block::dirt) = ivec2(2, 15);

	game::texture_atlas::association_for(game::block::dirt_with_grass).left = ivec2(3, 15);
	game::texture_atlas::association_for(game::block::dirt_with_grass).right = ivec2(3, 15);
	game::texture_atlas::association_for(game::block::dirt_with_grass).front = ivec2(3, 15);
	game::texture_atlas::association_for(game::block::dirt_with_grass).back = ivec2(3, 15);
	game::texture_atlas::association_for(game::block::dirt_with_grass).top = ivec2(12, 3);
	game::texture_atlas::association_for(game::block::dirt_with_grass).bottom = ivec2(2, 15);

	game::texture_atlas::association_for(game::block::water) = ivec2(13, 3);

	game::texture_atlas::association_for(game::block::blue_flower) = ivec2(12, 15);
}

void				application::application::initialize_player()
{
	engine::camera::create(); // TODO
	game::player::create();
}