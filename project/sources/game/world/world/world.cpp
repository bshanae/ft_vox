#include "world.h"

#include "application/common/debug/debug.h"

#include "engine/main/rendering/camera/camera/camera.h"

#include "game/world/tools/aabb/aabb.h"
#include "game/world/chunk/block/block_highlighter/block_highlighter/block_highlighter.h"
#include "game/world/chunk/chunk/chunk/chunk.h"
#include "game/world/chunk/chunk/rendering/chunk_renderer/chunk_renderer.h"
#include "game/world/chunk/generator/generator/generator.h"

using namespace				engine;
using namespace				game;

static const vec3			left = vec3(-chunk_settings::size[0], 0.f, 0.f);
static const vec3			right = vec3(+chunk_settings::size[0], 0.f, 0.f);
static const vec3			forward = vec3(0.f, 0.f, chunk_settings::size[2]);
static const vec3			back = vec3(0.f, 0.f, -chunk_settings::size[2]);

							world::world()
{
	set_layout("Opaque");
	update_timer = timer(world_settings::chunks_generation_time_limit);
}

optional<block_pointer>		world::world::find_block(const vec3 &position)
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

	index.x = (int)(position.x - chunk_position.x);
	index.y = (int)(position.y - chunk_position.y);
	index.z = (int)(position.z - chunk_position.z);

	chunk_position.y = 0;

	if (chunk = get_instance()->find_chunk(chunk_position); not chunk or not index)
		return {};
	else
		return block_pointer(chunk, index);
}

shared_ptr<chunk>			world::find_chunk(const vec3 &position)
{
	const auto 				instance = get_instance();
	shared_lock				lock(instance->map_mutex);

	if (auto iterator = instance->chunks.find(position); iterator != instance->chunks.end())
		return iterator->second;
	else
		return nullptr;
}

shared_ptr<chunk>			world::find_new_chunk(const vec3 &position)
{
	const auto 				instance = get_instance();
	const auto				iterator = instance->new_chunks.find(position);

	if (iterator != instance->new_chunks.end())
		return iterator->second;
	else
		return nullptr;
}

void						world::insert_block(const block_pointer &id, enum block_type type)
{
	id().set_type(type);
	get_instance()->request_rebuild(id.get_chunk(), id.get_index());
}

void						world::remove_block(const block_pointer &id)
{
	id().set_type(block_type::air);
	get_instance()->request_rebuild(id.get_chunk(), id.get_index());
}

void						world::select_block(const block_pointer &id, block_face face)
{
	block_highlighter::get_instance()->activate();

	block_highlighter::set_translation(id.get_world_position() + vec3(0.5f));
	block_highlighter::set_selected_face(face);
}

void						world::unselect_block()
{
	block_highlighter::get_instance()->deactivate();
}

bool						world::does_collide(const aabb &aabb)
{
	vec3 					min = glm::floor(aabb.min);
	vec3 					max = glm::floor(aabb.max);

	optional<block_pointer>	block_iterator;

	for (int x = (int)min.x; x <= (int)max.x; x++)
	for (int y = (int)min.y; y <= (int)max.y; y++)
	for (int z = (int)min.z; z <= (int)max.z; z++)
	{
		if (not (block_iterator = find_block(vec3(x, y, z))))
			continue ;

		if
		(
			is_solid(get_meta_type(block_iterator.value()().get_type())) and
			aabb::do_collide(aabb, block_iterator->get_aabb())
		)
		{
			return true;
		}
	}

	return false;
}

shared_ptr<chunk>			world::find_neighbor_chunk(const shared_ptr<chunk> &main, axis axis, sign sign)
{
	vec3					neighbor_position = main->get_position();

	if (axis == axis::x and sign == sign::minus)
		neighbor_position += left;
	else if (axis == axis::x and sign == sign::plus)
		neighbor_position += right;
	else if (axis == axis::z and sign == sign::minus)
		neighbor_position += back;
	else if (axis == axis::z and sign == sign::plus)
		neighbor_position += forward;
	else
		return nullptr;

	return find_chunk(neighbor_position);
}

// ------------------------ Pivot

float						world::distance(const vec3 &position)
{
	return glm::distance(pivot, position + chunk_settings::size_as_vector / 2.f);
}

float						world::distance(const shared_ptr<chunk> &chunk)
{
	return glm::distance(pivot, chunk->get_center());
}

// ------------------------ Object methods

void						world::when_initialized()
{
	create_chunk(vec3());
	create_chunk(left);
	create_chunk(right);
	create_chunk(forward);
	create_chunk(back);
}

void						world::when_deinitialized() {}

void						world::when_updated()
{
	update_timer.execute();

	pivot.x = camera::get_position().x;
	pivot.z = camera::get_position().z;

	for (auto [position, chunk] : chunks)
	{
		if (update_timer.get_state() == timer::finished)
			break;

		request_build(chunk);
	}

	for (auto [position, chunk] : chunks)
	{
		chunk->set_visible(distance(chunk) < world_settings::visibility_limit);

		if (update_timer.get_state() == timer::running)
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
		chunks.erase(chunk->get_position());
	old_chunks.clear();

	lock.unlock();
}

void						world::when_rendered()
{
	if (auto camera_block = find_block(camera::get_position()))
		chunk_renderer::set_apply_water_tint(camera_block.value()().get_type() == block_type::water);

	for (auto [position, chunk] : chunks)
		chunk_renderer::render(chunk, chunk_renderer::group::opaque);

	for (auto [position, chunk] : chunks)
		sorted_chunks.emplace(distance(chunk), chunk);

	for (auto iterator = sorted_chunks.rbegin(); iterator != sorted_chunks.rend(); ++iterator)
	{
		chunk_renderer::render(iterator->second, chunk_renderer::group::partially_transparent);
		chunk_renderer::render(iterator->second, chunk_renderer::group::transparent);
	}

	sorted_chunks.clear();
}

// ------------------------ Additional methods

bool						world::create_chunk_if_needed(const vec3 &position)
{
	if (distance(position) >= world_settings::cashing_limit)
		return false;
	if (find_chunk(position) != nullptr)
		return false;
	if (find_new_chunk(position) != nullptr)
		return false;

	create_chunk(position);
	return true;
}

bool						world::destroy_chunk_if_needed(const shared_ptr<chunk> &chunk)
{
	if (distance(chunk) >= world_settings::cashing_limit)
	{
		destroy_chunk(chunk);
		return true;
	}

	return false;
}

void						world::create_chunk(const vec3 &position)
{
	auto					chunk = make_shared<game::chunk>(position);

	generator::generate(chunk);
	new_chunks.emplace(position, chunk);
}

void						world::destroy_chunk(const shared_ptr<chunk> &chunk)
{
	old_chunks.push_back(chunk);
}

void						world::request_build(const shared_ptr<chunk> &chunk)
{
	chunk->update_build_if_needed();
}

void						world::request_rebuild(const shared_ptr<chunk> &chunk, const chunk::index &changed_block)
{
	static auto				find_and_rebuild = [](const vec3 &position)
	{
		auto				chunk = find_chunk(position);

		if (debug::check(chunk != nullptr, "[world] Can't rebuild chunk"))
			chunk->reset_build();
	};

	if (changed_block.x == 0)
		find_and_rebuild(chunk->get_position() + left);
	else if (changed_block.x == chunk_settings::size[0] - 1)
		find_and_rebuild(chunk->get_position() + right);

	if (changed_block.z == 0)
		find_and_rebuild(chunk->get_position() + back);
	else if (changed_block.z == chunk_settings::size[2] - 1)
		find_and_rebuild(chunk->get_position() + forward);

	chunk->reset_build();
}