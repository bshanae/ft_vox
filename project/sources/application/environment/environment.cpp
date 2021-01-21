#include "environment.h"

#include "engine/rendering/main/layout/layout/layout.h"
#include "engine/rendering/main/layout/layout_manager/layout_manager.h"
#include "engine/rendering/ui/font/font_library/font_library.h"
#include "engine/rendering/ui/font/symbol/symbol_renderer.h"
#include "engine/rendering/main/camera/camera.h"
#include "engine/processor/processor.h"

#include "game/world/utils/texture_atlas/texture_atlas.h"
#include "game/world/world/world.h"
#include "game/world/chunk/block/block_selector/block_selector/block_selector.h"
#include "game/world/chunk/block/block_selector/block_selector_renderer/block_selector_renderer.h"
#include "game/world/chunk/chunk/chunk_renderer/chunk_renderer.h"
#include "game/world/chunk/generator/generator/generator.h"
#include "game/player/player.h"

					environment::environment()
{
	initialize_engine();
	initialize_ui();
	initialize_game();
	initialize_player();
}

void 				environment::execute()
{
	engine::processor::get_instance()->execute();
}

void 				environment::initialize_engine()
{
	engine::processor::construct();

	engine::layout_manager::add("System");
	engine::layout_manager::add("Opaque", engine::layout::use_depth_test);
	engine::layout_manager::add("Transparent", engine::layout::use_depth_test);
	engine::layout_manager::add("UI");
}

void 				environment::initialize_ui()
{
	ui::font_library::construct();
	ui::symbol_renderer::construct();
}

void 				environment::initialize_game()
{
	game::generator::construct();
	game::biome_collection::construct();
	game::block_selector::construct();
	game::block_selector_renderer::construct();
	game::chunk_renderer::construct();
	game::world::construct();

	initialize_texture_atlas();
}

void 				environment::initialize_texture_atlas()
{
	game::texture_atlas::construct();

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

void				environment::initialize_player()
{
	engine::camera::construct(); // TODO
	game::player::construct();
}