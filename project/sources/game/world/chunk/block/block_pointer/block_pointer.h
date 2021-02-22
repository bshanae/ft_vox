#pragma once

#include "game/world/chunk/block/block_face/block_face.h"
#include "game/world/chunk/chunk/chunk/chunk_settings.h"
#include "game/world/chunk/chunk/chunk/chunk.h"

namespace					game
{
	enum class 				axis;
	enum class 				sign;

	class					aabb;

	class					block;
	class					world;

	class					block_pointer;
}

class						game::block_pointer final
{
	using					chunk_type = shared_ptr<chunk>;
	using					index_type = chunk_settings::underlying_array::index;

public :
							block_pointer();
							block_pointer(const shared_ptr<::game::chunk> &chunk, const index_type &index);
							block_pointer(const block_pointer &other);

	block_pointer			&operator = (const block_pointer &other);

	block					&operator * () const;
	block					*operator -> () const;

	bool					is_valid() const;

	chunk_type				get_chunk() const;
	index_type				get_index() const;
	block_pointer			get_neighbor(block_face face) const;
	block_pointer			get_neighbor(axis axis, sign sign) const;
	block_pointer			get_neighbor(const chunk::index &offset) const;
	vec3					get_world_position() const;
	aabb					get_aabb() const;

private :

	block					*raw_pointer;

	chunk_type				chunk;
	index_type				index;
};
