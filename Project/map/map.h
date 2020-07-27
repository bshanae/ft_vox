#pragma once

#include "common/aliases.h"
#include "common/global.h"
#include "application/unique_object.h"
#include "map/chunk.h"

static
inline
constexpr int			map_size[3] = {4, 1, 4};

class					map :
							public array3<shared_ptr<chunk>, map_size[2], map_size[1], map_size[0]>,
							public unique_object<map>
{
public :
						map();
						~map() override = default;
private :

	using 				index_map_type = std::map<shared_ptr<chunk>, index>;
	index_map_type		index_map;

	static
	shared_ptr<chunk>	provide_neighbor_chunk(
						const shared_ptr<chunk> &main,
						axis axis,
						sign sign);
};