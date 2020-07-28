#include "map.h"

static const vec3		left = vec3(-chunk_size[0], 0.f, 0.f);
static const vec3		right = vec3(+chunk_size[0], 0.f, 0.f);
static const vec3		forward = vec3(0.f, 0.f, chunk_size[2]);
static const vec3		back = vec3(0.f, 0.f, -chunk_size[2]);

						map::map()
{
	create_chunk_if_needed(vec3(0));
	create_chunk_if_needed(left);
	create_chunk_if_needed(right);
	create_chunk_if_needed(forward);
	create_chunk_if_needed(back);
	chunk::neighbor_provider = &map::provide_neighbor_chunk;
}

#include "camera/camera.h"

void					map::early_update()
{
#warning "This should be done by player"
	position.x = camera::get_position().x;
	position.z = camera::get_position().z;

	for (auto [position, chunk] : chunks)
	{
		create_chunk_if_needed(position + left);
		create_chunk_if_needed(position + right);
		create_chunk_if_needed(position + forward);
		create_chunk_if_needed(position + back);
	}
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
		neighbor_position += forward;
	else if (axis == axis::z and sign == sign::plus)
		neighbor_position += back;
	else
		return (nullptr);

	if (auto iterator = instance()->chunks.find(neighbor_position); iterator != instance()->chunks.end())
		return (iterator->second);
	else
		return (nullptr);
}

void					map::create_chunk_if_needed(const vec3 &position)
{
	if (distance(this->position, position) >= map_settings::cashing_limit)
		return ;
	if (auto iterator = chunks.find(position); iterator != chunks.end())
		return ;

	chunks[position] = chunk::create(position);
}

void					map::destroy_chunk_if_needed(const shared_ptr<chunk> &chunk)
{
	if (distance(this->position, position) >= map_settings::cashing_limit)
		;// destroy
}