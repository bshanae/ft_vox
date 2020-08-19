#pragma once

#include "common/OpenGL.h"
#include "common/array3.h"

#include "world/block/block.h"

struct							chunk_settings
{
	static constexpr int		size[3] = {16, 16, 16};
	static inline const vec3	size_as_vector = vec3(size[0], size[1], size[2]);

	using						underlying_array = array3<block, chunk_settings::size[0], chunk_settings::size[1], chunk_settings::size[2]>;
};