#pragma once

#include "game/world/block/block_face/block_face.h"
#include "game/world/chunk/chunk/chunk_settings.h"
#include "game/world/chunk/chunk/chunk.h"

namespace					game
{
	enum class 				axis;
	enum class 				sign;

	class					aabb;

	class					block;
	class					world;

	class					block_ptr;
}

class						game::block_ptr final
{
	using					chunk_type = shared_ptr<chunk>;
	using					index_type = chunk_settings::underlying_array::index;

public :
							block_ptr();
							block_ptr(const shared_ptr<::game::chunk> &chunk, const index_type &index);
							block_ptr(const block_ptr &other);

	block_ptr				&operator = (const block_ptr &other);
	block					&operator * () const;
	block					*operator -> () const;

	bool					operator == (const nullptr_t &ptr) const;
	bool					operator != (const nullptr_t &ptr) const;
							operator bool () const;

	chunk_type				get_chunk() const;
	index_type				get_index() const;
	block_ptr				get_neighbor(block_face face) const;
	block_ptr				get_neighbor(axis axis, sign sign) const;
	block_ptr				get_neighbor(const chunk::index &offset) const;
	vec3					get_world_position() const;
	aabb					get_aabb() const;

private :

	block					*raw_ptr;

	chunk_type				chunk;
	index_type				index;
};
