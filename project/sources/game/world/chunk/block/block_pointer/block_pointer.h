#pragma once

#include "game/world/chunk/chunk/chunk/chunk_settings.h"

namespace					game
{
	enum class 				axis;
	enum class 				sign;

	class					aabb;

	class					block;
	class					chunk;
	class					world;

	class					block_pointer;
}

class						game::block_pointer final
{
	using					chunk_type = shared_ptr<chunk>;
	using					index_type = chunk_settings::underlying_array::index;

public :
							block_pointer(const shared_ptr<::game::chunk> &chunk, const index_type &index);
							block_pointer(const block_pointer &other);

	block_pointer			&operator = (const block_pointer &other);
	block					&operator () () const;

	[[nodiscard]]
	chunk_type				get_chunk() const;

	[[nodiscard]]
	index_type				get_index() const;

	[[nodiscard]]
	optional<block_pointer>	get_neighbor(axis axis, sign sign) const;

	[[nodiscard]] vec3		get_world_position() const;
	[[nodiscard]] aabb		get_aabb() const;

private :

	chunk_type				_chunk;
	index_type				_index;
};
