#include "block_alias.h"

#include "game/world/utils/aabb/aabb.h"
#include "game/world/utils/array3/array3.h"
#include "game/world/chunk/chunk/chunk/chunk.h"
#include "game/world/world/world.h"

using namespace			game;

						block_alias::block_alias(const shared_ptr<::chunk> &chunk, const chunk::index &index)
{
	this->chunk = chunk;
	this->index = index;
}

block_alias::chunk_type	block_alias::get_chunk() const
{
	return chunk;
}

block_alias::index_type	block_alias::get_index() const
{
	return index;
}

block					&block_alias::operator () () const
{
	return (chunk->at(index));
}

optional<block_alias>	block_alias::get_neighbor(axis axis, sign sign) const
{
	auto				neighbor_index = index.get_neighbor((::axis)axis, (::sign)sign);

	if (neighbor_index)
		return (block_alias(chunk, neighbor_index));
	else
	{
		chunk::index	reflected_index;
		chunk_type		neighbor_chunk;

		if ((neighbor_chunk = world::get_instance()->find_neighbor_chunk(chunk, axis, sign)) == nullptr)
			return {};

		neighbor_index = index.get_neighbor(axis, sign);
		reflected_index = neighbor_index.reflect();

		return (block_alias(neighbor_chunk, reflected_index));
	}
}

vec3					block_alias::get_world_position() const
{
	return (vec3)chunk->get_position() + (vec3)index;
}

aabb					block_alias::get_aabb() const
{
	static const vec3	epsilon = vec3(0.08f);

	vec3				min = get_world_position();
	vec3				max = get_world_position() + vec3(1.f);

	min -= epsilon;
	max += epsilon;

	return {min, max};
}