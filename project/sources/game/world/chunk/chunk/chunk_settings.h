#pragma once

#include "game/world/tools/array3/array3.h"
#include "game/world/block/block/block.h"

#include "application/common/imports/opengl.h"

namespace						game
{
	struct						chunk_settings;
}

struct							game::chunk_settings
{
	static constexpr int		size[3] = {32, 256, 32};
	static inline const vec3	size_as_vector = vec3(size[0], size[1], size[2]);

	using						underlying_array = array3<block, chunk_settings::size[0], chunk_settings::size[1], chunk_settings::size[2]>;
};