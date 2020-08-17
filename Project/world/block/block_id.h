#pragma once

#include "world/chunk/chunk_settings.h"

class					chunk;

struct					block_id
{
	friend class		block;
	friend class		chunk;
	friend class		world;

	[[nodiscard]]
	block				&operator () () const;

	[[nodiscard]]
	optional<block_id>	neighbor(axis axis, sign sign) const;

	[[nodiscard]] vec3	world_position() const;

private :

	using				chunk_type = shared_ptr<chunk>;
	using				index_type = chunk_settings::underlying_array::index;

						block_id(const shared_ptr<::chunk> &chunk, const index_type &index);

	chunk_type			chunk;
	index_type			index;
};
