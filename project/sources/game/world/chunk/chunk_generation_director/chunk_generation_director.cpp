#include "chunk_generation_director.h"

#include "application/common/utilities/type_utility.h"

#include "game/world/chunk/chunk_workspace/chunk_workspace.h"

#include "game/world/world/world.h"

using namespace					game;

								chunk_generation_director::chunk_generation_director()
{
	set_layout("System");
}

optional<chunk_build>			chunk_generation_director::process_build(const shared_ptr<chunk> &chunk)
{
	auto 						instance = get_instance();

	if (instance->get_state() == state::deinitialized)
		return nullopt;

	return instance->get_or_create_worker(chunk)->process();
}

void							chunk_generation_director::reset_build(const shared_ptr<chunk> &chunk)
{
	const auto 					instance = get_instance();

	if (get_instance()->get_state() == state::deinitialized)
		return;

	instance->drop_worker(chunk);
	instance->get_or_create_worker(chunk)->process(true);
}

void 							chunk_generation_director::delete_build(const shared_ptr<chunk> &chunk)
{
	if (get_instance()->get_state() == state::deinitialized)
		return;

	get_instance()->drop_worker(chunk);
}

void 							chunk_generation_director::when_deinitialized()
{
#if !FT_VOX_FORCE_EXIT
	active_workers.clear();
	dropped_workers.clear();
#endif
}

void 							chunk_generation_director::when_updated()
{
	for (auto iterator = dropped_workers.begin(); iterator != dropped_workers.end();)
	{
		if (not (*iterator)->is_busy())
			iterator = dropped_workers.erase(iterator);
		else
			iterator++;
	}
}
								chunk_generation_director::worker_ptr
								chunk_generation_director::get_or_create_worker(const shared_ptr<chunk> &chunk)
{
	if (not active_workers.contains(chunk))
		active_workers.emplace(chunk, make_shared<chunk_generation_worker>(chunk));

	return active_workers.at(chunk);
}

void 							chunk_generation_director::drop_worker(const shared_ptr<chunk> &chunk)
{
	if (auto iterator = active_workers.find(chunk); iterator != active_workers.end())
	{
		dropped_workers.push_back(iterator->second);
		active_workers.erase(iterator);
	}
}

bool							chunk_generation_director::is_chunk_present_and_has_light(const vec3 &position)
{
//	shared_ptr<chunk>			chunk;
//	const workspace_and_task	*workspace;
//
//	chunk = world::get_map().find(position);
//	if (chunk == nullptr)
//		return false;
//
//	workspace = get_instance()->get_workspace_and_task(chunk);
//	if (workspace == nullptr)
//		return false;
//
//	return true;
//	return workspace->get_state() >= chunk_workspace::light_done;
}

bool							chunk_generation_director::are_all_neighbors_present_and_have_light(const shared_ptr<chunk> &chunk)
{
//	return
//	(
//		is_chunk_present_and_has_light(chunk->get_position() + left) and
//		is_chunk_present_and_has_light(chunk->get_position() + right) and
//		is_chunk_present_and_has_light(chunk->get_position() + forward) and
//		is_chunk_present_and_has_light(chunk->get_position() + back)
//	);
}