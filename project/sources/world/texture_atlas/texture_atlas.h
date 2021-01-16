#pragma once

#include "common/imports/opengl.h"
#include "common/classes/singleton.h"
#include "common/imports/std.h"
#include "engine/model/texture/texture.h"
#include "world/block/block/block.h"

namespace					world
{
	class					chunk_renderer;

	class					texture_atlas;
}


class						world::texture_atlas :
								public singleton<texture_atlas>,
								public engine::texture
{
	friend class			chunk_renderer;

public :

	explicit				texture_atlas(const path &source);
							~texture_atlas() override = default;

	struct					association
	{
		explicit			association(enum block::type type);

		association			&operator = (const ivec2 &value);

		ivec2 				left;
		ivec2 				right;
		ivec2 				top;
		ivec2 				bottom;
		ivec2 				back;
		ivec2 				front;

	private :

		enum block::type	type;
	};

	static association		&association_for(enum block::type type);

	static vec2 			texture_size();

private :

	static
	inline
	constexpr int			texture_size_in_pixels[2] = {48, 48};

	ivec2 					number_of_textures = ivec2(0);

	using 					associations_type = map<enum block::type, association>;
	associations_type		associations;
};