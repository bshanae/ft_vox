#include "engine/core/core.h"
#include "ui/font/font_library.h"
#include "ui/font/symbol_renderer.h"
#include "world/texture_atlas/texture_atlas.h"
#include "world/world/world.h"
#include "world/block/block_selector.h"
#include "world/block/block_selector_renderer.h"
#include "world/chunk/chunk_renderer.h"
#include "world/loader/loader.h"
#include "player/camera/camera.h"
#include "player/player/player.h"

#include "ui/text/text.h"
#include "ui/font/font.h"

int						main()
{
	core::initialize();

	core::register_layout("System", false);
	core::register_layout("Opaque", true);
	core::register_layout("Transparent", true);
	core::register_layout("UI", false);

	font_library::create();
	symbol_renderer::create();

	loader::create();
	block_selector::create();
	block_selector_renderer::create();
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

	auto text = text::create();

	text->position = vec2(0.5f);
	text->font = font::create("project/resources/fonts/HelveticaNeue.ttc", 50);

	core::execute();

	return (0);
}
