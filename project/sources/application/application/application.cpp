#include "application.h"

#include "engine/main/rendering/layout/layout/layout.h"
#include "engine/main/rendering/layout/layout_manager/layout_manager.h"
#include "engine/extensions/ui/font/font_library/font_library.h"
#include "engine/extensions/ui/font/symbol/symbol_renderer.h"
#include "engine/main/rendering/camera/camera.h"
#include "engine/main/processor/processor.h"

#include "game/world/skybox/skybox.h"
#include "game/world/world/world.h"
#include "game/world/chunk/texture_atlas/texture_atlas.h"
#include "game/world/chunk/block/block_highlighter/block_highlighter/block_highlighter.h"
#include "game/world/chunk/block/block_highlighter/block_highlighter_renderer/block_highlighter_renderer.h"
#include "game/world/chunk/chunk/chunk_renderer/chunk_renderer.h"
#include "game/world/chunk/generator/generator/generator.h"
#include "game/player/player/player.h"

					application::application()
{
	initialize_engine();
	initialize_ui();
	initialize_game();
	initialize_player();
}

void 				application::execute()
{
	engine::processor::execute();
}

void 				application::initialize_engine()
{
	engine::processor::construct();

	engine::layout_manager::add("System");
	engine::layout_manager::add("Background");
	engine::layout_manager::add("Opaque", engine::layout::use_depth_test);
	engine::layout_manager::add("Transparent", engine::layout::use_depth_test);
	engine::layout_manager::add("UI");
}

void 				application::initialize_ui()
{
	engine::ui::font_library::construct();
	engine::ui::symbol_renderer::construct();
}

void 				application::initialize_game()
{
	game::skybox::construct();
	game::generator::construct();
	game::biome_collection::construct();
	game::block_highlighter::construct();
	game::block_highlighter_renderer::construct();
	game::chunk_renderer::construct();
	game::world::construct();

	initialize_texture_atlas();
}

void 				application::initialize_texture_atlas()
{
	game::texture_atlas::construct();

	game::texture_atlas::get_association(game::block_type::stone) = ivec2(1, 15);

	game::texture_atlas::get_association(game::block_type::dirt) = ivec2(2, 15);

	game::texture_atlas::get_association(game::block_type::dirt_with_grass).left = ivec2(3, 15);
	game::texture_atlas::get_association(game::block_type::dirt_with_grass).right = ivec2(3, 15);
	game::texture_atlas::get_association(game::block_type::dirt_with_grass).front = ivec2(3, 15);
	game::texture_atlas::get_association(game::block_type::dirt_with_grass).back = ivec2(3, 15);
	game::texture_atlas::get_association(game::block_type::dirt_with_grass).top = ivec2(12, 3);
	game::texture_atlas::get_association(game::block_type::dirt_with_grass).bottom = ivec2(2, 15);

	game::texture_atlas::get_association(game::block_type::water) = ivec2(13, 3);

	game::texture_atlas::get_association(game::block_type::blue_flower) = ivec2(12, 15);
}

void				application::initialize_player()
{
	engine::camera::construct(); // TODO
	game::player::construct();
}