#include "block_id.h"

#include "world/chunk/chunk.h"
#include "world/world/world.h"

block					&block_id::operator () () const
{
	return (chunk->at(index));
}

optional<block_id>		block_id::neighbor(axis axis, sign sign) const
{
	auto				neighbor_index = index.neighbor((::axis)axis, (::sign)sign);

	if (neighbor_index)
		return (block_id(chunk, neighbor_index));
	else
	{
		chunk::index	reflected_index;
		chunk_type		neighbor_chunk;

		if ((neighbor_chunk = world::find_neighbor_chunk(chunk, axis, sign)) == nullptr)
			return {};

		neighbor_index = index.neighbor(axis, sign);
		reflected_index = neighbor_index.reflect();

		return (block_id(neighbor_chunk, reflected_index));
	}
}

						block_id::block_id(const shared_ptr<::chunk> &chunk, const chunk::index &index)
{
	this->chunk = chunk;
	this->index = index;
}