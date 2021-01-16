#pragma once

#include "game/world/utils/array3/array3.h"
#include "game/world/chunk/block/block/block.h"

#include "application/common/imports/opengl.h"

namespace						world
{
	struct						chunk_settings;
}

struct							world::chunk_settings
{
	static constexpr int		size[3] = {16, 64, 16};
	static inline const vec3	size_as_vector = vec3(size[0], size[1], size[2]);

	using						underlying_array = array3<block, chunk_settings::size[0], chunk_settings::size[1], chunk_settings::size[2]>;
};