#include "map.h"

#include "chunk_loader.h"
#include "chunk_generator.h"

static const vec3		left = vec3(-chunk_settings::size[0], 0.f, 0.f);
static const vec3		right = vec3(+chunk_settings::size[0], 0.f, 0.f);
static const vec3		forward = vec3(0.f, 0.f, chunk_settings::size[2]);
static const vec3		back = vec3(0.f, 0.f, -chunk_settings::size[2]);

						map::map()
{
	chunk::neighbor_provider = &map::provide_neighbor_chunk;
}

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
	destroy_implementation();
	for (auto &iterator : chunks)
		chunk_loader::upload(iterator.second);
}

#include "camera/camera.h"

void					map::update()
{
#warning "This should be done by player"
	pivot.x = camera::position->x;
	pivot.z = camera::position->z;

	for (auto [position, chunk] : chunks)
	{
		create_chunk_if_needed(position + left);
		create_chunk_if_needed(position + right);
		create_chunk_if_needed(position + forward);
		create_chunk_if_needed(position + back);

		destroy_chunk_if_needed(chunk);
	}

#warning "Needs fix"
	for (auto [position, chunk] : chunks)
		if (not chunk->model)
			try_start_chunk(chunk);
}

shared_ptr<chunk>		map::provide_neighbor_chunk(
							const shared_ptr<chunk> &main,
							axis axis,
							sign sign)
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

void					map::create_chunk_if_needed(const vec3 &position)
{
	if (distance(this->pivot, position + chunk_settings::size_as_vector / 2.f) >= map_settings::cashing_limit)
		return ;
	if (auto iterator = chunks.find(position); iterator != chunks.end())
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

void 					map::try_start_chunk(const shared_ptr<chunk> &chunk)
{
	if (auto iterator = chunks.find(*chunk->position + left); iterator == chunks.end())
		return ;
	if (auto iterator = chunks.find(*chunk->position + right); iterator == chunks.end())
		return ;
	if (auto iterator = chunks.find(*chunk->position + forward); iterator == chunks.end())
		return ;
	if (auto iterator = chunks.find(*chunk->position + back); iterator == chunks.end())
		return ;

	chunk->build();
}