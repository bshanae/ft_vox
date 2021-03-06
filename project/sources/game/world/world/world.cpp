#include "world.h"

#include "application/common/debug/debug.h"

#include "engine/main/rendering/camera/camera/camera.h"

#include "game/world/tools/aabb/aabb.h"
#include "game/world/block/block_highlighter/block_highlighter/block_highlighter.h"
#include "game/world/chunk/chunk/chunk.h"
#include "game/world/chunk/chunk_renderer/chunk_renderer.h"

using namespace				engine;
using namespace				game;

							world::world() : pivot(0, 0, 0)
{
	set_layout("Opaque");
}

block_ptr					world::find_block(const vec3 &position)
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

	if (chunk = get_instance()->chunks.find(chunk_position); chunk != nullptr and index.is_valid())
		return block_ptr(chunk, index);
	else
		return block_ptr();
}

shared_ptr<chunk>			world::find_chunk(const vec3 &position)
{
	return get_instance()->chunks.find(position);
}

void						world::insert_block(const block_ptr &block, enum block_type type)
{
	block->set_type(type);
	get_instance()->rebuild_chunk_and_maybe_neighbors(block.get_chunk(), block.get_index());
}

void						world::remove_block(const block_ptr &block)
{
	block->set_type(block_type::air);
	get_instance()->rebuild_chunk_and_maybe_neighbors(block.get_chunk(), block.get_index());
}

void						world::select_block(const block_ptr &block, block_face face)
{
	block_highlighter::highlight(block, face);
}

void						world::unselect_block()
{
	block_highlighter::reset();
}

float						world::distance(const vec3 &position)
{
	return glm::distance(get_instance()->pivot, position + chunk_settings::size_as_vector / 2.f);
}

float						world::distance(const shared_ptr<chunk> &chunk)
{
	return glm::distance(get_instance()->pivot, chunk->get_center());
}

bool						world::does_collide(const aabb &aabb)
{
	vec3 					min = floor(aabb.min);
	vec3 					max = floor(aabb.max);

	block_ptr				block_iterator;

	for (int x = (int)min.x; x <= (int)max.x; x++)
	for (int y = (int)min.y; y <= (int)max.y; y++)
	for (int z = (int)min.z; z <= (int)max.z; z++)
	{
		if (block_iterator = find_block(vec3(x, y, z)); not block_iterator)
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

void						world::when_initialized()
{
	create_chunk(vec3());
}

void						world::when_updated()
{
	engine::timer			timer{world_settings::chunks_generation_time_limit};

	update_pivot();

	for (const auto &[position, chunk] : chunks)
	{
		if (timer.did_finish())
			break;

		update_chunk_build(chunk);
		update_chunk_visibility(chunk);
		create_chunk_neighbors_if_needed(chunk);
		destroy_chunk_if_needed(chunk);
	}

	update_chunk_map();
}

void						world::when_rendered()
{
	if (auto camera_block = find_block(camera::get_position()); camera_block)
		chunk_renderer::set_apply_water_tint(camera_block->get_type() == block_type::water);
	else
		chunk_renderer::set_apply_water_tint(false);

	for (auto [position, chunk] : chunks)
		chunk_renderer::render(chunk, chunk_renderer::group::opaque);

	for (auto [position, chunk] : chunks)
	{
		chunk_renderer::render(chunk, chunk_renderer::group::partially_transparent);
		chunk_renderer::render(chunk, chunk_renderer::group::transparent);
	}
}

void						world::update_pivot()
{
	pivot.x = camera::get_position().x;
	pivot.z = camera::get_position().z;
}

void						world::update_chunk_map()
{
	chunks.process_added_chunks();
	chunks.process_removed_chunks();
}

void						world::update_chunk_build(const shared_ptr<chunk> &chunk)
{
	chunk->update_build_if_needed();
}

void						world::update_chunk_visibility(const shared_ptr<chunk> &chunk)
{
	chunk->set_visible(distance(chunk) < world_settings::visibility_limit);
}

void						world::create_chunk_neighbors_if_needed(const shared_ptr<chunk> &chunk)
{
	const auto 				position = chunk->get_position();

	create_chunk_if_needed(position + chunk::left_offset);
	create_chunk_if_needed(position + chunk::right_offset);
	create_chunk_if_needed(position + chunk::forward_offset);
	create_chunk_if_needed(position + chunk::back_offset);
}

void 						world::create_chunk_if_needed(const vec3 &position)
{
	if (distance(position) >= world_settings::cashing_limit)
		return;
	if (chunks.find(position) != nullptr)
		return;

	create_chunk(position);
}

void						world::destroy_chunk_if_needed(const shared_ptr<chunk> &chunk)
{
	if (distance(chunk) >= world_settings::cashing_limit)
		destroy_chunk(chunk);
}

void 						world::create_chunk(const vec3 &position)
{
	chunks.add_later(make_shared<game::chunk>(position));
}

void						world::destroy_chunk(const shared_ptr<chunk> &chunk)
{
	chunk->delete_build();
	chunks.remove_later(chunk);
}

void 						world::rebuild_chunk(const shared_ptr<chunk> &chunk)
{
	chunk->reset_build();
}

void						world::rebuild_chunk_and_maybe_neighbors(const shared_ptr<chunk> &chunk, const chunk::index &changed_block)
{
	if (changed_block.x == 0)
		rebuild_chunk_if_exist(chunk->get_position() + chunk::left_offset);
	else if (changed_block.x == chunk_settings::size[0] - 1)
		rebuild_chunk_if_exist(chunk->get_position() + chunk::right_offset);

	if (changed_block.z == 0)
		rebuild_chunk_if_exist(chunk->get_position() + chunk::back_offset);
	else if (changed_block.z == chunk_settings::size[2] - 1)
		rebuild_chunk_if_exist(chunk->get_position() + chunk::forward_offset);

	rebuild_chunk(chunk);
}

void 						world::rebuild_chunk_if_exist(const vec3 &position)
{
	if (auto chunk = chunks.find(position); chunk != nullptr)
		rebuild_chunk(chunk);
	else
		debug::check(chunk != nullptr, "[world] Can't rebuild chunk");
}