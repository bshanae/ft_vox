#include "map.h"

#include "chunk_loader.h"
#include "chunk_generator.h"

static const vec3		left = vec3(-chunk_settings::size[0], 0.f, 0.f);
static const vec3		right = vec3(+chunk_settings::size[0], 0.f, 0.f);
static const vec3		forward = vec3(0.f, 0.f, chunk_settings::size[2]);
static const vec3		back = vec3(0.f, 0.f, -chunk_settings::size[2]);

						map::map() {}

shared_ptr<chunk>		map::find_chunk(const vec3 &position)
{
	auto				iterator = instance()->chunks.find(position);

	if (iterator != instance()->chunks.end())
		return (iterator->second);
	else
		return (nullptr);
}

optional<block_id>		map::find_block(const vec3 &position)
{
	chunk::index		index;
	vec3				chunk_position;
	shared_ptr<chunk>	chunk;

	index.x = (int)position.x % chunk_settings::size[0];
	index.y = (int)position.y % chunk_settings::size[1];
	index.z = (int)position.z % chunk_settings::size[2];

	chunk_position.x = (int)position.x - index.x;
	chunk_position.y = (int)position.y - index.y;
	chunk_position.z = (int)position.z - index.z;

	if (chunk = find_chunk(chunk_position); not chunk)
		return {};
	else
		return (block_id(chunk, index));
}

void					map::insert_block(const vec3 &position, enum block::type type)
{
	auto 				block = find_block(position);

	assert(block and (*block)().is_empty() and "Chunk for the block doesn't exist or block is not empty");

}

void					map::remove_block(const vec3 &position)
{

}

shared_ptr<chunk>		map::neighbor_chunk(const shared_ptr<chunk> &main, axis axis, sign sign)
{
	vec3				neighbor_position = main->position;

	if (axis == axis::x and sign == sign::minus)
		neighbor_position += left;
	else if (axis == axis::x and sign == sign::plus)
		neighbor_position += right;
	else if (axis == axis::z and sign == sign::minus)
		neighbor_position += back;
	else if (axis == axis::z and sign == sign::plus)
		neighbor_position += forward;
	else
		return (nullptr);

	if (auto iterator = instance()->chunks.find(neighbor_position); iterator != instance()->chunks.end())
		return (iterator->second);
	else
		return (nullptr);
}

// --------------------	Object methods

void					map::initialize_implementation()
{
	create_chunk(vec3());
	create_chunk(left);
	create_chunk(right);
	create_chunk(forward);
	create_chunk(back);
}

void					map::deinitialize_implementation()
{
	for (auto &iterator : chunks)
		chunk_loader::upload(iterator.second);
}

#include "camera/camera.h"

void					map::update()
{
#warning "This should be done by player"
//	pivot.x = camera::position->x;
//	pivot.z = camera::position->z;

	for (auto [position, chunk] : chunks)
	{
		create_chunk_if_needed(position + left);
		create_chunk_if_needed(position + right);
		create_chunk_if_needed(position + forward);
		create_chunk_if_needed(position + back);

		destroy_chunk_if_needed(chunk);
	}

	for (auto [position, chunk] : chunks)
		if (chunk->build_phase != chunk::build_phase::model_done)
			try_build_chunk(chunk);
}

// -------------------- Additional methods

void					map::create_chunk_if_needed(const vec3 &position)
{
	if (distance(this->pivot, position + chunk_settings::size_as_vector / 2.f) >= map_settings::cashing_limit)
		return ;
	if (find_chunk(position) != nullptr)
		return ;

	create_chunk(position);
}

void					map::destroy_chunk_if_needed(const shared_ptr<chunk> &chunk)
{
	if (distance(this->pivot, (vec3)chunk->center) >= map_settings::cashing_limit)
		destroy_chunk(chunk);
}

void					map::create_chunk(const vec3 &position)
{
	shared_ptr<chunk>	chunk;

	if (not (chunk = chunk_loader::download(position)))
		chunk = chunk::create(position);

#warning "Generation module needed"
//	if (not (chunk = chunk_loader::download(position)))
//		chunk = chunk_generator::generate(position);

	chunks[position] = chunk;
}

void					map::destroy_chunk(const shared_ptr<chunk> &chunk)
{
	chunk_loader::upload(chunk);
	chunks.erase(chunk->position);
	chunk->destroy();
}

void 					map::try_build_chunk(const shared_ptr<chunk> &chunk)
{
	switch (chunk->build_phase)
	{
		case (chunk::build_phase::nothing_done) :
			chunk->build(chunk::build_request::light);
			break ;

		case (chunk::build_phase::light_done) :
			if (find_chunk(*chunk->position + left) == nullptr)
				return;
			if (find_chunk(*chunk->position + right) == nullptr)
				return;
			if (find_chunk(*chunk->position + forward) == nullptr)
				return;
			if (find_chunk(*chunk->position + back) == nullptr)
				return;

			chunk->build(chunk::build_request::model);
			break ;

		default :
			assert(false and "Unexpected chunk build circumstance");
	}
}