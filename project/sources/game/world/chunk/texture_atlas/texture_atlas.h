#pragma once

#include "engine/main/rendering/texture/texture/texture.h"

#include "game/world/chunk/block/block/block.h"

#include "application/common/imports/opengl.h"
#include "application/common/templates/singleton/singleton.h"
#include "application/common/imports/glm.h"
#include "application/common/imports/std.h"

namespace						game
{
	class						chunk_renderer;
	class						texture_atlas;
}

class							game::texture_atlas : public singleton<texture_atlas>
{
	friend class				chunk_renderer;

public :
								texture_atlas();
								~texture_atlas() override = default;

	struct						association
	{
		explicit				association(enum block::type type);

		association				&operator = (const ivec2 &value);

		ivec2 					left;
		ivec2 					right;
		ivec2 					top;
		ivec2 					bottom;
		ivec2 					back;
		ivec2 					front;

	private :

		enum block::type		type;
	};

	static
	shared_ptr<engine::texture>	get_texture();
	static vec2 				get_texture_size();

	static association			&get_association(enum block::type type);

private :

	using 						associations_type = map<enum block::type, association>;

	static inline constexpr int	texture_size_in_pixels[2] = {48, 48};

	shared_ptr<engine::texture>	texture;
	ivec2 						number_of_textures = ivec2(0);
	associations_type			associations;
};