#include "block_pointer.h"

#include "game/world/tools/aabb/aabb.h"
#include "game/world/tools/array3/array3.h"
#include "game/world/chunk/chunk/chunk/chunk.h"
#include "game/world/world/world.h"

using namespace				game;

							block_pointer::block_pointer(const shared_ptr<::chunk> &chunk, const chunk::index &index)
{
	_chunk = chunk;
	_index = index;
}

							block_pointer::block_pointer(const block_pointer &other)
{
	this->_chunk = other._chunk;
	this->_index = other._index;
}

block_pointer				&block_pointer::operator = (const block_pointer &other)
{
	if (this == &other)
		return *this;

	this->_chunk = other._chunk;
	this->_index = other._index;

	return *this;
}

block_pointer::chunk_type	block_pointer::get_chunk() const
{
	return _chunk;
}

block_pointer::index_type	block_pointer::get_index() const
{
	return _index;
}

block						&block_pointer::operator () () const
{
	return (_chunk->at(_index));
}

optional<block_pointer>		block_pointer::get_neighbor(axis axis, sign sign) const
{
	auto					neighbor_index = _index.get_neighbor((::axis)axis, (::sign)sign);

	if (neighbor_index)
		return block_pointer(_chunk, neighbor_index);
	else
	{
		chunk::index		reflected_index;
		chunk_type			neighbor_chunk;

		if ((neighbor_chunk = world::get_instance()->find_neighbor_chunk(_chunk, axis, sign)) == nullptr)
			return {};

		neighbor_index = _index.get_neighbor(axis, sign);
		reflected_index = neighbor_index.reflect();

		return block_pointer(neighbor_chunk, reflected_index);
	}
}

vec3						block_pointer::get_world_position() const
{
	return _chunk->get_position() + (vec3)_index;
}

aabb						block_pointer::get_aabb() const
{
	static const vec3		epsilon = vec3(0.08f);

	vec3					min = get_world_position();
	vec3					max = get_world_position() + vec3(1.f);

	min -= epsilon;
	max += epsilon;

	return {min, max};
}