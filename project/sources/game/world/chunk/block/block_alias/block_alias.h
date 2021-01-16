#pragma once

#include "game/world/chunk/chunk/chunk/chunk_settings.h"

namespace					world
{
	enum class 				axis;
	enum class 				sign;

	class					aabb;

	class					block;
	class					chunk;
	class					world;

	class					block_alias;
}

class						world::block_alias
{
	friend class			::world::block;
	friend class			::world::chunk;
	friend class			::world::world;

public :

	block					&operator () () const;

	optional<block_alias>	get_neighbor(axis axis, sign sign) const;

	vec3					world_position() const;
	aabb					aabb() const;

private :

	using					chunk_type = shared_ptr<chunk>;
	using					index_type = chunk_settings::underlying_array::index;

							block_alias(const shared_ptr<::world::chunk> &chunk, const index_type &index);

	chunk_type				chunk;
	index_type				index;
};
