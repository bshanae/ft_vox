#include "launcher.h"

#include "engine/main/rendering/layout/layout_manager/layout_manager.h"
#include "engine/extensions/utilities/fps_counter/fps_counter.h"
#include "engine/extensions/ui/font/font_library/font_library.h"
#include "engine/extensions/ui/font/symbol/symbol_renderer.h"

#include "game/world/skybox/skybox.h"
#include "game/world/world/world.h"
#include "game/world/texture_atlas/texture_atlas/texture_atlas.h"
#include "game/world/block/block_highlighter/block_highlighter/block_highlighter.h"
#include "game/world/block/block_highlighter/block_highlighter_renderer/block_highlighter_renderer.h"
#include "game/world/chunk/chunk_generation_director/chunk_generation_director.h"
#include "game/world/chunk/chunk_renderer/chunk_renderer.h"
#include "game/player/player/player.h"

using namespace 	game;

void 				launcher::construct_engine_extension_objects()
{
	engine::utilities::fps_counter::construct();

	engine::ui::font_library::construct();
	engine::ui::symbol_renderer::construct();
}

void				launcher::setup_layouts()
{
	engine::layout_manager::add("System");
	engine::layout_manager::add("Background");
	engine::layout_manager::add("Opaque", engine::layout::use_depth_test);
	engine::layout_manager::add("Transparent", engine::layout::use_depth_test);
	engine::layout_manager::add("UI");
}

void				launcher::construct_objects()
{
	game::skybox::construct();
	game::texture_atlas::construct();

	game::block_highlighter::construct();
	game::block_highlighter_renderer::construct();

	game::chunk_generation_director::construct();
	game::chunk_renderer::construct();
	game::world::construct();

	game::player::construct();
}

void				launcher::setup_texture_atlas()
{
	//				Solid

	game::texture_atlas::get_coordinates(game::block_type::dirt).set_all({2, 15});

	game::texture_atlas::get_coordinates(game::block_type::dirt_with_grass).set_all({3, 15});
	game::texture_atlas::get_coordinates(game::block_type::dirt_with_grass).set_top({12, 3});
	game::texture_atlas::get_coordinates(game::block_type::dirt_with_grass).set_bottom({2, 15});

    game::texture_atlas::get_coordinates(game::block_type::sand).set_all({2, 14});

    game::texture_atlas::get_coordinates(game::block_type::stone).set_all({1, 15});

	game::texture_atlas::get_coordinates(game::block_type::stone_with_snow).set_all({1, 15});
	game::texture_atlas::get_coordinates(game::block_type::stone_with_snow).set_top({2, 11});

	game::texture_atlas::get_coordinates(game::block_type::wood).set_all({4, 14});
	game::texture_atlas::get_coordinates(game::block_type::wood).set_top({5, 14});
	game::texture_atlas::get_coordinates(game::block_type::wood).set_bottom({5, 14});

    game::texture_atlas::get_coordinates(game::block_type::cloud).set_all({3, 2});

	//				Transparent

	game::texture_atlas::get_coordinates(game::block_type::water).set_all({13, 3});

	game::texture_atlas::get_coordinates(game::block_type::leaves).set_all({11, 1});

	//				Diagonal

	game::texture_atlas::get_coordinates(game::block_type::blue_flower).set_all({12, 15});

	game::texture_atlas::get_coordinates(game::block_type::mushroom).set_all({12, 14});
}