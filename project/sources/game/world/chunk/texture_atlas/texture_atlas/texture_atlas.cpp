#include "texture_atlas.h"

#include "application/common/debug/debug.h"

#include "engine/main/rendering/texture/texture_loader/texture_loader.h"

using namespace				game;

							texture_atlas::texture_atlas()
{
	texture = engine::texture_loader::load("project/resources/atlases/default.png");

	debug::check_critical
	(
		texture->get_width() % texture_size_in_pixels[0] == 0 &&
		texture->get_height() % texture_size_in_pixels[1] == 0,
		"[texture_atlas] Can't index texture atlas"
	);

	number_of_textures.x = texture->get_width() / texture_size_in_pixels[0];
	number_of_textures.y = texture->get_height() / texture_size_in_pixels[1];

}

vec2						texture_atlas::get_texture_size()
{
	return
	{
		1.f / (float)get_instance()->number_of_textures.x,
		1.f / (float)get_instance()->number_of_textures.y
	};
}

game::texture_coordinates	&texture_atlas::get_coordinates(block_type type)
{
	const auto 				instance = texture_atlas::get_instance();
	const auto				lock_guard = std::lock_guard(instance->mutex);

	const auto 				iterator = instance->map.find(type);

	if (iterator == instance->map.end())
		instance->map.try_emplace(type);

	return instance->map.at(type);
}

void						texture_atlas::use(bool state)
{
	get_instance()->texture->use(state);
}