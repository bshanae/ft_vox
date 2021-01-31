#include "texture_atlas.h"

#include "engine/main/rendering/texture/texture_loader/texture_loader.h"

#include "application/common/debug/debug.h"

using namespace				game;

							texture_atlas::texture_atlas()
{
	texture = engine::texture_loader::load("project/resources/atlases/default.png");

	debug::check_critical
	(
		texture->get_width() % texture_size_in_pixels[0] == 0 &&
		texture->get_height() % texture_size_in_pixels[1] == 0,
		"[game::texture_atlas] Can't index texture atlas"
	);

	number_of_textures.x = texture->get_width() / texture_size_in_pixels[0];
	number_of_textures.y = texture->get_height() / texture_size_in_pixels[1];

}

texture_atlas::association	&texture_atlas::association::operator = (const ivec2 &value)
{
	left = value;
	right = value;
	top = value;
	bottom = value;
	back = value;
	front = value;

	return *this;
}

shared_ptr<engine::texture>	texture_atlas::get_texture()
{
	return get_instance()->texture;
}

vec2						texture_atlas::get_texture_size()
{
	return
	{
		1.f / (float)get_instance()->number_of_textures.x,
		1.f / (float)get_instance()->number_of_textures.y
	};
}

texture_atlas::association	&texture_atlas::get_association(enum block_type type)
{
	auto 					instance = texture_atlas::get_instance();
	auto 					iterator = instance->associations.find(type);

	if (iterator == instance->associations.end())
		instance->associations.try_emplace(type);

	return instance->associations.at(type);
}