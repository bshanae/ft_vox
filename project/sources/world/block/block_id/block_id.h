#pragma once

#include "world/chunk/chunk_settings.h"
#include "world/aabb/aabb.h"

namespace				world
{
	class				block;
	class				chunk;
	class				world;

	class				block_id;
}

class					world::block_id
{
	friend class		::world::block;
	friend class		::world::chunk;
	friend class		::world::world;

public :

	block				&operator () () const;

	optional<block_id>	neighbor(axis axis, sign sign) const;

	vec3				world_position() const;
	aabb				aabb() const;

private :

	using				chunk_type = shared_ptr<chunk>;
	using				index_type = chunk_settings::underlying_array::index;

						block_id(const shared_ptr<::world::chunk> &chunk, const index_type &index);

	chunk_type			chunk;
	index_type			index;
};
