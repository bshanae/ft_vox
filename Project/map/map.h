#pragma once

#include "common/aliases.h"
#include "map/chunk.h"

class				map
{
public :
					map() = default;
					~map() = default;
private :

	static
	inline
	constexpr int	size[3] = {1, 1, 1};

	using			chunks_type = array<array<array<chunk, size[2]>, size[1]>, size[0]>;
};


