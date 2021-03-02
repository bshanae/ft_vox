#include "block_ptr.h"

#include "game/world/tools/aabb/aabb.h"
#include "game/world/tools/array3/array3.h"
#include "game/world/world/world.h"

using namespace				game;

							block_ptr::block_ptr()
{
	this->chunk = nullptr;
	this->index = chunk::index();
	this->raw_ptr = nullptr;
}

							block_ptr::block_ptr(const shared_ptr<::chunk> &chunk, const chunk::index &index)
{
	this->chunk = chunk;
	this->index = index;
	this->raw_ptr = &chunk->at(index);
}

							block_ptr::block_ptr(const block_ptr &other)
{
	this->chunk = other.chunk;
	this->index = other.index;
	this->raw_ptr = other.raw_ptr;
}

block_ptr					&block_ptr::operator = (const block_ptr &other)
{
	if (this == &other)
		return *this;

	this->chunk = other.chunk;
	this->index = other.index;
	this->raw_ptr = other.raw_ptr;

	return *this;
}

bool						block_ptr::operator == (const nullptr_t &ptr) const
{
	return raw_ptr == nullptr;
}

							block_ptr::operator bool () const
{
	return *this != nullptr;
}

block						&block_ptr::operator * () const
{
	return *raw_ptr;
}

block						*block_ptr::operator -> () const
{
	return raw_ptr;
}

block_ptr::chunk_type		block_ptr::get_chunk() const
{
	return chunk;
}

block_ptr::index_type		block_ptr::get_index() const
{
	return index;
}

block_ptr					block_ptr::get_neighbor(block_face face) const
{
	const auto 				[axis, sign] = to_axis_and_sign(face);

	return get_neighbor(axis, sign);
}

block_ptr					block_ptr::get_neighbor(axis axis, sign sign) const
{
	auto					neighbor_index = index.get_neighbor(axis, sign);

	if (neighbor_index.is_valid())
		return block_ptr(chunk, neighbor_index);
	else
		return world::find_block(chunk->get_position() + (vec3)neighbor_index);
}

block_ptr					block_ptr::get_neighbor(const chunk::index &offset) const
{
	auto					neighbor_index = index + offset;

	if (neighbor_index.is_valid())
		return block_ptr(chunk, neighbor_index);
	else
		return world::find_block(chunk->get_position() + (vec3)neighbor_index);
}

vec3						block_ptr::get_world_position() const
{
	return chunk->get_position() + (vec3)index;
}

aabb						block_ptr::get_aabb() const
{
	static const vec3		epsilon = vec3(0.08f);

	vec3					min = get_world_position();
	vec3					max = get_world_position() + vec3(1.f);

	min -= epsilon;
	max += epsilon;

	return {min, max};
}