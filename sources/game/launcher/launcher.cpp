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
#include "game/world/chunk/generation/chunk_generation_director/chunk_generation_director.h"
#include "game/world/chunk/chunk_renderer/chunk_renderer.h"
#include "game/world/chunk/generation/utilities/biome/biome_generator/biome_generator.h"
#include "game/world/chunk/generation/utilities/biome/biomes/plain/plain.h"
#include "game/world/chunk/generation/utilities/biome/biomes/forest/forest.h"
#include "game/world/chunk/generation/utilities/biome/biomes/desert/desert.h"
#include "game/world/chunk/generation/utilities/biome/biomes/mountains/mountains.h"
#include "game/world/chunk/generation/utilities/biome/biomes/lakes/lakes.h"
#include "game/player/player/player.h"
#include "game/ui/info/info.h"

#include "engine/extensions/ui/font/font/font.h"

using namespace 	game;

void				launcher::setup_layouts()
{
	engine::layout_manager::add("System");
	engine::layout_manager::add("Background");
	engine::layout_manager::add("Opaque", engine::layout::use_depth_test);
	engine::layout_manager::add("Transparent", engine::layout::use_depth_test);
	engine::layout_manager::add("UI");
}

void 				launcher::construct_engine_extension_objects()
{
	engine::utilities::fps_counter::construct();

	engine::ui::font_library::construct();
	engine::ui::symbol_renderer::construct();
}

void				launcher::construct_game_objects()
{
	game::skybox::construct();
	game::texture_atlas::construct();

	game::block_highlighter::construct();
	game::block_highlighter_renderer::construct();

	game::chunk_generation_director::construct();
	game::chunk_renderer::construct();
	game::world::construct();
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

	game::texture_atlas::get_coordinates(game::block_type::stone_with_snow).set_all({7, 3});
	game::texture_atlas::get_coordinates(game::block_type::stone_with_snow).set_top({2, 11});

	game::texture_atlas::get_coordinates(game::block_type::wood).set_all({4, 14});
	game::texture_atlas::get_coordinates(game::block_type::wood).set_top({5, 14});
	game::texture_atlas::get_coordinates(game::block_type::wood).set_bottom({5, 14});

	game::texture_atlas::get_coordinates(game::block_type::leaves).set_all({12, 1});

    game::texture_atlas::get_coordinates(game::block_type::cloud).set_all({3, 2});

	//				Transparent

	game::texture_atlas::get_coordinates(game::block_type::water).set_all({13, 3});

	//				Diagonal

	game::texture_atlas::get_coordinates(game::block_type::grass).set_all({10, 10});

	game::texture_atlas::get_coordinates(game::block_type::blue_flower).set_all({12, 15});

	game::texture_atlas::get_coordinates(game::block_type::mushroom).set_all({12, 14});
}

void				launcher::setup_biomes()
{
	game::biome_generator::register_biome<biomes::plain>(10);
	game::biome_generator::register_biome<biomes::forest>(10);
	game::biome_generator::register_biome<biomes::desert>(10);
	game::biome_generator::register_biome<biomes::mountains>(10);
	game::biome_generator::register_biome<biomes::lakes>(10);
}

void 				launcher::construct_player()
{
	game::player::construct();
}

void					launcher::setup_ui()
{
	game::ui::info::construct();
}