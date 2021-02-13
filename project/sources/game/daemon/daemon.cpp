#include "daemon.h"

#include "engine/main/rendering/layout/layout_manager/layout_manager.h"
#include "engine/extensions/utilities/fps_counter/fps_counter.h"
#include "engine/extensions/ui/font/font_library/font_library.h"
#include "engine/extensions/ui/font/symbol/symbol_renderer.h"

#include "game/world/skybox/skybox.h"
#include "game/world/world/world.h"
#include "game/world/chunk/texture_atlas/texture_atlas/texture_atlas.h"
#include "game/world/chunk/block/block_highlighter/block_highlighter/block_highlighter.h"
#include "game/world/chunk/block/block_highlighter/block_highlighter_renderer/block_highlighter_renderer.h"
#include "game/world/chunk/chunk/rendering/chunk_renderer/chunk_renderer.h"
#include "game/world/chunk/generator/generator/generator.h"
#include "game/player/player/player.h"

using namespace 	game;

void 				daemon::construct_engine_extension_objects()
{
	engine::utilities::fps_counter::construct();

	engine::ui::font_library::construct();
	engine::ui::symbol_renderer::construct();
}

void				daemon::setup_layouts()
{
	engine::layout_manager::add("System");
	engine::layout_manager::add("Background");
	engine::layout_manager::add("Opaque", engine::layout::use_depth_test);
	engine::layout_manager::add("Transparent", engine::layout::use_depth_test);
	engine::layout_manager::add("UI");
}

void				daemon::construct_objects()
{
	game::player::construct();

	game::skybox::construct();

	game::texture_atlas::construct();
	game::biome_collection::construct();
	game::generator::construct();

	game::block_highlighter::construct();
	game::block_highlighter_renderer::construct();
	game::chunk_renderer::construct();
	game::world::construct();
}

void				daemon::setup_texture_atlas()
{
	game::texture_atlas::get_coordinates(game::block_type::stone).set_all(ivec2(1, 15));

	game::texture_atlas::get_coordinates(game::block_type::dirt).set_all(ivec2(2, 15));

	game::texture_atlas::get_coordinates(game::block_type::dirt_with_grass).set_left(ivec2(3, 15));
	game::texture_atlas::get_coordinates(game::block_type::dirt_with_grass).set_right(ivec2(3, 15));
	game::texture_atlas::get_coordinates(game::block_type::dirt_with_grass).set_front(ivec2(3, 15));
	game::texture_atlas::get_coordinates(game::block_type::dirt_with_grass).set_back(ivec2(3, 15));
	game::texture_atlas::get_coordinates(game::block_type::dirt_with_grass).set_top(ivec2(12, 3));
	game::texture_atlas::get_coordinates(game::block_type::dirt_with_grass).set_bottom(ivec2(2, 15));

	game::texture_atlas::get_coordinates(game::block_type::water).set_all(ivec2(13, 3));

	game::texture_atlas::get_coordinates(game::block_type::blue_flower).set_all(ivec2(12, 15));
}
