#include "texture_atlas.h"

#include "application/common/debug/debug.h"

#include "engine/main/rendering/texture/texture_loader/texture_loader.h"

using namespace				game;

							texture_atlas::texture_atlas()
{
	_texture = engine::texture_loader::load("project/resources/atlases/default.png");

	debug::check_critical
	(
		_texture->get_width() % texture_size_in_pixels[0] == 0 &&
		_texture->get_height() % texture_size_in_pixels[1] == 0,
		"[game::texture_atlas] Can't index texture atlas"
	);

	_number_of_textures.x = _texture->get_width() / texture_size_in_pixels[0];
	_number_of_textures.y = _texture->get_height() / texture_size_in_pixels[1];

}

vec2						texture_atlas::get_texture_size()
{
	return
	{
		1.f / (float)get_instance()->_number_of_textures.x,
		1.f / (float)get_instance()->_number_of_textures.y
	};
}

game::texture_coordinates	&texture_atlas::get_coordinates(block_type type)
{
	auto 					instance = texture_atlas::get_instance();
	auto 					iterator = instance->_map.find(type);

	if (iterator == instance->_map.end())
		instance->_map.try_emplace(type);

	return instance->_map.at(type);
}

void						texture_atlas::use(bool state)
{
	get_instance()->_texture->use(state);
}