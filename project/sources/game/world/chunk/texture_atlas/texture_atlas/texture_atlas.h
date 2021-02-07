#pragma once

#include "application/common/imports/opengl.h"
#include "application/common/templates/singleton/singleton.h"
#include "application/common/imports/glm.h"
#include "application/common/imports/std.h"

#include "engine/main/rendering/texture/texture/texture.h"

#include "game/world/chunk/block/block/block.h"
#include "game/world/chunk/texture_atlas/texture_coordinates/texture_coordinates.h"

namespace								game
{
	enum class							block_type;
	class								chunk_renderer;
	class								texture_atlas;
}

class									game::texture_atlas : public singleton<texture_atlas>
{
	friend class						chunk_renderer;

public :
										texture_atlas();
										~texture_atlas() override = default;

	static vec2 						get_texture_size();
	static texture_coordinates			&get_coordinates(block_type type);

	static void 						use(bool state);

private :

	using 								map_type = map<block_type, texture_coordinates>;

	static inline constexpr int			texture_size_in_pixels[2] = {48, 48};

	shared_ptr<engine::texture>			texture;
	ivec2 								number_of_textures = ivec2(0);
	map_type							map;
	shared_mutex						mutex;
};