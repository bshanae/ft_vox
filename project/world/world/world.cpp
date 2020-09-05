#include "world.h"

#include "engine/time/timestamp.h"
#include "world/block/block_selector/block_selector.h"
#include "world/chunk/chunk_renderer.h"
#include "world/generator/generator/generator.h"
#include "world/loader/loader/loader.h"
#include "player/camera/camera.h"

using namespace				engine;
using namespace				player;

static const vec3			left = vec3(-world::chunk_settings::size[0], 0.f, 0.f);
static const vec3			right = vec3(+world::chunk_settings::size[0], 0.f, 0.f);
static const vec3			forward = vec3(0.f, 0.f, world::chunk_settings::size[2]);
static const vec3			back = vec3(0.f, 0.f, -world::chunk_settings::size[2]);

							world::world::world()
{
	usual_object::layout = "Opaque";
	update_timer = timer(world_settings::chunk_generation_time_limit);
}

optional<::world::block_id>	world::world::find_block(const vec3 &position)
{
	chunk::index			index;
	vec3					chunk_position;
	shared_ptr<chunk>		chunk;

	chunk_position.x = floor(position.x / chunk_settings::size[0]);
	chunk_position.y = floor(position.y / chunk_settings::size[1]);
	chunk_position.z = floor(position.z / chunk_settings::size[2]);

	chunk_position.x *= chunk_settings::size[0];
	chunk_position.y *= chunk_settings::size[1];
	chunk_position.z *= chunk_settings::size[2];

	index.x = position.x - chunk_position.x;
	index.y = position.y - chunk_position.y;
	index.z = position.z - chunk_position.z;

	chunk_position.y = 0;

	if (chunk = find_chunk(chunk_position); not chunk or not index)
		return {};
	else
		return (block_id(chunk, index));
}

void						world::world::insert_block(const block_id &id, enum block::type type)
{
	id().type = type;
	id.chunk->can_be_regenerated = false;
	instance()->rebuild_chunk(id.chunk, id.index);
}

void						world::world::remove_block(const block_id &id)
{
	id().type = block::type::air;
	id.chunk->can_be_regenerated = false;
	instance()->rebuild_chunk(id.chunk, id.index);
}

void						world::world::select_block(const block_id &id, block::face face)
{
	block_selector::instance()->activate();
	block_selector::instance()->translation = id.world_position() + vec3(0.5f);
	block_selector::instance()->selected_face = face;
}

void						world::world::unselect_block()
{
	block_selector::instance()->deactivate();
}

bool						world::world::does_collide(const aabb &aabb)
{
	vec3 					min = glm::floor(aabb.min);
	vec3 					max = glm::floor(aabb.max);

	optional<block_id>		block_iterator;

	for (int x = (int)min.x; x <= (int)max.x; x++)
		for (int y = (int)min.y; y <= (int)max.y; y++)
			for (int z = (int)min.z; z <= (int)max.z; z++)
			{
				if (not (block_iterator = find_block(vec3(x, y, z))))
					continue ;
				if ((*block_iterator)().is_solid() and aabb::do_collide(aabb, block_iterator->aabb()))
					return (true);
			}

	return (false);
}

shared_ptr<world::chunk>	world::world::find_neighbor_chunk(const shared_ptr<chunk> &main, axis axis, sign sign)
{
	vec3					neighbor_position = main->position;

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

	return (find_chunk(neighbor_position));
}

shared_ptr<world::chunk>	world::world::find_chunk(const vec3 &position)
{
	shared_lock				lock(instance()->map_mutex);

	auto					iterator = instance()->chunks.find(position);

	if (iterator != instance()->chunks.end())
		return (iterator->second);
	else
		return (nullptr);
}

shared_ptr<world::chunk>	world::world::find_new_chunk(const vec3 &position)
{
	auto					iterator = instance()->new_chunks.find(position);

	if (iterator != instance()->new_chunks.end())
		return (iterator->second);
	else
		return (nullptr);
}

// ------------------------ Pivot

float						world::world::distance(const vec3 &position)
{
	return (glm::distance(pivot, position + chunk_settings::size_as_vector / 2.f));
}

float						world::world::distance(const shared_ptr<chunk> &chunk)
{
	return (glm::distance(pivot, (vec3)chunk->center));
}

// ------------------------ Object methods

void						world::world::initialize_implementation()
{
	create_chunk(vec3());
	create_chunk(left);
	create_chunk(right);
	create_chunk(forward);
	create_chunk(back);
}

void						world::world::deinitialize_implementation()
{
	for (auto [position, chunk] : chunks)
		if (not chunk->can_be_regenerated)
			loader::upload(chunk);
}

void						world::world::update()
{
	update_timer.execute();

	pivot.x = camera::position->x;
	pivot.z = camera::position->z;

	for (auto [position, chunk] : chunks)
		if (update_timer.state == timer::state::finished)
			break;
		else if (chunk->build_phase != chunk::build_phase::model_done)
			try_build_chunk(chunk);

	for (auto [position, chunk] : chunks)
	{
		chunk->is_visible = distance(chunk) < world_settings::visibility_limit;

		if (update_timer.state == timer::state::running)
		{
			create_chunk_if_needed(position + left);
			create_chunk_if_needed(position + right);
			create_chunk_if_needed(position + forward);
			create_chunk_if_needed(position + back);

			destroy_chunk_if_needed(chunk);
		}
	}

	unique_lock				lock(map_mutex);

	for (auto [position, chunk] : new_chunks)
		chunks[position] = chunk;
	new_chunks.clear();

	for (auto &chunk : old_chunks)
		chunks.erase(chunk->position);
	old_chunks.clear();

	lock.unlock();
}

void						world::world::render()
{
	if (auto camera_block = find_block((vec3)camera::position))
		chunk_renderer::apply_water_tint = (*camera_block)().type == block::type::water;

	for (auto [position, chunk] : chunks)
		chunk_renderer::render(chunk, chunk::batch_purpose::opaque);

	for (auto [position, chunk] : chunks)
			sorted_chunks.emplace(distance(chunk), chunk);

	for (auto iterator = sorted_chunks.rbegin(); iterator != sorted_chunks.rend(); ++iterator)
	{
		chunk_renderer::render(iterator->second, chunk::batch_purpose::partially_transparent);
		chunk_renderer::render(iterator->second, chunk::batch_purpose::transparent);
	}

	sorted_chunks.clear();
}

// ------------------------ Additional methods

bool						world::world::create_chunk_if_needed(const vec3 &position)
{
	if (distance(position) >= world_settings::cashing_limit)
		return (false);
	if (find_chunk(position) != nullptr)
		return (false);
	if (find_new_chunk(position) != nullptr)
		return (false);

	create_chunk(position);
	return (true);
}

bool						world::world::destroy_chunk_if_needed(const shared_ptr<chunk> &chunk)
{
	if (distance(chunk) >= world_settings::cashing_limit)
	{
		destroy_chunk(chunk);
		return (true);
	}

	return (false);
}

void						world::world::create_chunk(const vec3 &position)
{
	auto					chunk = make_shared<::world::chunk>(position);

	if (loader::download(chunk))
		chunk->can_be_regenerated = false;
	else
		generator::generate(chunk);

	new_chunks.emplace(position, chunk);
}

void						world::world::destroy_chunk(const shared_ptr<chunk> &chunk)
{
	if (not chunk->can_be_regenerated)
		loader::upload(chunk);
	old_chunks.push_back(chunk);
}

void						world::world::try_build_chunk(const shared_ptr<chunk> &chunk)
{
	static auto				chunk_exist_and_has_light = [](const vec3 &position)
	{
		auto				chunk = find_chunk(position);

		return (chunk and chunk->build_phase >= chunk::build_phase::light_done);
	};

	switch (chunk->build_phase)
	{
		case (chunk::build_phase::nothing_done) :
			chunk->build(chunk::build_request::light);
			break ;

		case (chunk::build_phase::light_in_process) :
			chunk->wait(chunk::build_request::light);
			break ;

		case (chunk::build_phase::light_done) :
			if
			(
				chunk_exist_and_has_light(*chunk->position + left) and
				chunk_exist_and_has_light(*chunk->position + right) and
				chunk_exist_and_has_light(*chunk->position + forward) and
				chunk_exist_and_has_light(*chunk->position + back)
			)
				chunk->build(chunk::build_request::geometry);
			break ;

		case (chunk::build_phase::geometry_in_process) :
			chunk->wait(chunk::build_request::geometry);
			break ;

		case (chunk::build_phase::geometry_done) :
			chunk->build(chunk::build_request::model);
			break ;

		default :
			assert(false and "Unexpected chunk build circumstances");
	}
}

void						world::world::rebuild_chunk(const shared_ptr<chunk> &chunk, const chunk::index &changed_block)
{
	static auto				find_and_rebuild = [](const vec3 &position)
	{
		auto				chunk = find_chunk(position);

		assert(chunk);
		chunk->build(chunk::build_request::reset);
	};

	if (changed_block.x == 0)
		find_and_rebuild(*chunk->position + left);
	else if (changed_block.x == chunk_settings::size[0] - 1)
		find_and_rebuild(*chunk->position + right);

	if (changed_block.z == 0)
		find_and_rebuild(*chunk->position + back);
	else if (changed_block.z == chunk_settings::size[2] - 1)
		find_and_rebuild(*chunk->position + forward);

	chunk->build(chunk::build_request::reset);
}