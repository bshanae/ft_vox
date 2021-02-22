#include "block_pointer.h"

#include "game/world/tools/aabb/aabb.h"
#include "game/world/tools/array3/array3.h"
#include "game/world/world/world.h"

using namespace				game;

							block_pointer::block_pointer()
{
	this->chunk = nullptr;
	this->index = chunk::index();
	this->raw_pointer = nullptr;
}

							block_pointer::block_pointer(const shared_ptr<::chunk> &chunk, const chunk::index &index)
{
	this->chunk = chunk;
	this->index = index;
	this->raw_pointer = &chunk->at(index);
}

							block_pointer::block_pointer(const block_pointer &other)
{
	this->chunk = other.chunk;
	this->index = other.index;
	this->raw_pointer = other.raw_pointer;
}

block_pointer				&block_pointer::operator = (const block_pointer &other)
{
	if (this == &other)
		return *this;

	this->chunk = other.chunk;
	this->index = other.index;
	this->raw_pointer = other.raw_pointer;

	return *this;
}

block						&block_pointer::operator * () const
{
	return *raw_pointer;
}

block						*block_pointer::operator -> () const
{
	return raw_pointer;
}

bool						block_pointer::is_valid() const
{
	return chunk != nullptr;
}

block_pointer::chunk_type	block_pointer::get_chunk() const
{
	return chunk;
}

block_pointer::index_type	block_pointer::get_index() const
{
	return index;
}

block_pointer				block_pointer::get_neighbor(block_face face) const
{
	const auto 				[axis, sign] = to_axis_and_sign(face);

	return get_neighbor(axis, sign);
}

block_pointer				block_pointer::get_neighbor(axis axis, sign sign) const
{
	auto					neighbor_index = index.get_neighbor(axis, sign);

	if (neighbor_index.is_valid())
		return block_pointer(chunk, neighbor_index);
	else
		return world::find_block(chunk->get_position() + (vec3)neighbor_index);
}

block_pointer				block_pointer::get_neighbor(const chunk::index &offset) const
{
	auto					neighbor_index = index + offset;

	if (neighbor_index.is_valid())
		return block_pointer(chunk, neighbor_index);
	else
		return world::find_block(chunk->get_position() + (vec3)neighbor_index);
}

vec3						block_pointer::get_world_position() const
{
	return chunk->get_position() + (vec3)index;
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