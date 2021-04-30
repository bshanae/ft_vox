#pragma once

#include "game/world/block/block_type/block_type/block_type.h"
#include "game/world/block/block_ptr/block_ptr.h"

namespace				game::biomes
{
	class 				abstract;
}

class					game::biomes::abstract
{
public :

	virtual				~abstract() = default;

	virtual int			generate_height(const vec2 &column) const = 0;
	virtual block_type	generate_block(int current_height, int total_height, bool is_cave, bool is_cloud) const = 0;
	virtual void		generate_decoration(const block_ptr &block, bool is_height_affected_by_cave) const = 0;
};