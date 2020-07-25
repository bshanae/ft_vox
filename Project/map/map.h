#pragma once

#include "common/aliases.h"
#include "map/chunk.h"

class				map
{
public :
					map()
	{
		for (auto &iterator : chunks)
		{
//			iterator->get_value() = chunk();
//			iterator->get_value().offset = iterator->get_index().to_glm();
		}
	}
					~map() = default;
private :

	static
	inline
	constexpr int	size[3] = {4, 4, 4};

	using			chunks_type = array3<chunk, size[2], size[1], size[0]>;
	chunks_type		chunks;
};