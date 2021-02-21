#include "world.h"

#include "application/common/debug/debug.h"

#include "engine/main/rendering/camera/camera/camera.h"

#include "game/world/tools/aabb/aabb.h"
#include "game/world/chunk/block/block_highlighter/block_highlighter/block_highlighter.h"
#include "game/world/chunk/chunk/chunk/chunk.h"
#include "game/world/chunk/chunk/rendering/chunk_renderer/chunk_renderer.h"

using namespace				engine;
using namespace				game;

static const vec3			left = vec3(-chunk_settings::size[0], 0.f, 0.f);
static const vec3			right = vec3(+chunk_settings::size[0], 0.f, 0.f);
static const vec3			forward = vec3(0.f, 0.f, chunk_settings::size[2]);
static const vec3			back = vec3(0.f, 0.f, -chunk_settings::size[2]);

#pragma region Main methods

							world::world()
{
	set_layout("Opaque");
}

block_pointer				world::world::find_block(const vec3 &position)
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

	if (chunk = get_instance()->find_chunk(chunk_position); chunk != nullptr and index.is_valid())
		return block_pointer(chunk, index);
	else
		return block_pointer();
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

void						world::insert_block(const block_pointer &block, enum block_type type)
{
	block->set_type(type);
	get_instance()->request_rebuild(block.get_chunk(), block.get_index());
}

void						world::remove_block(const block_pointer &block)
{
	block->set_type(block_type::air);
	get_instance()->request_rebuild(block.get_chunk(), block.get_index());
}

void						world::select_block(const block_pointer &block, block_face face)
{
	block_highlighter::get_instance()->activate();

	// TODO Move to block_highlighter
	block_highlighter::set_translation(block.get_world_position() + vec3(0.5f));
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

	block_pointer			block_iterator;

	for (int x = (int)min.x; x <= (int)max.x; x++)
	for (int y = (int)min.y; y <= (int)max.y; y++)
	for (int z = (int)min.z; z <= (int)max.z; z++)
	{
		if (block_iterator = find_block(vec3(x, y, z)); not block_iterator.is_valid())
			continue ;

		if
		(
			is_solid(get_meta_type(block_iterator->get_type())) and
			aabb::do_collide(aabb, block_iterator.get_aabb())
		)
		{
			return true;
		}
	}

	return false;
}

// TODO Remove
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

#pragma endregion

#pragma region Pivot

float						world::distance(const vec3 &position)
{
	return glm::distance(pivot, position + chunk_settings::size_as_vector / 2.f);
}

float						world::distance(const shared_ptr<chunk> &chunk)
{
	return glm::distance(pivot, chunk->get_center());
}

#pragma endregion

#pragma region Object methods

void						world::when_initialized()
{
	create_chunk(vec3());
	create_chunk(left);
	create_chunk(right);
	create_chunk(forward);
	create_chunk(back);

	// TODO This doesn't work, because landscape generation is now async
	// Immediately add first chunks
	process_new_chunks();
}

void						world::when_updated()
{
	update_timer = timer(world_settings::chunks_generation_time_limit);

	update_pivot();

	update_chunks_builds();
	destroy_far_chunks();

	process_new_chunks();
	process_old_chunks();
}

void						world::when_rendered()
{
	if (auto camera_block = find_block(camera::get_position()); camera_block.is_valid())
		chunk_renderer::set_apply_water_tint(camera_block->get_type() == block_type::water);
	else
		chunk_renderer::set_apply_water_tint(false);

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

#pragma endregion

#pragma region Additional methods

void						world::update_pivot()
{
	pivot.x = camera::get_position().x;
	pivot.z = camera::get_position().z;
}

void						world::update_chunks_builds()
{
	for (auto [position, chunk] : chunks)
	{
//		if (update_timer.did_finish())
//			break;

		request_build(chunk);
	}
}

void						world::destroy_far_chunks()
{
	for (auto [position, chunk] : chunks)
	{
//		if (update_timer.did_finish())
//			break;

		chunk->set_visible(distance(chunk) < world_settings::visibility_limit);

		if (update_timer.is_running())
		{
			create_chunk_if_needed(position + left);
			create_chunk_if_needed(position + right);
			create_chunk_if_needed(position + forward);
			create_chunk_if_needed(position + back);

			destroy_chunk_if_needed(chunk);
		}
	}
}

void						world::process_new_chunks()
{
	lock_guard				lock(map_mutex);

	for (auto [position, chunk] : new_chunks)
		chunks[position] = chunk;
	new_chunks.clear();
}

void						world::process_old_chunks()
{
	lock_guard				lock(map_mutex);

	for (auto &chunk : old_chunks)
		chunks.erase(chunk->get_position());
	old_chunks.clear();
}

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
	new_chunks.emplace(position, make_shared<game::chunk>(position));
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

#pragma endregion