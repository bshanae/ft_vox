#include "chunk_generation_director.h"

#include "application/common/utilities/type_utility.h"

#include "game/world/chunk/generation/utilities/chunk_workspace/chunk_workspace.h"
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

	return find_or_create_worker(chunk).process();
}

void							chunk_generation_director::reset_build(const shared_ptr<chunk> &chunk)
{
	const auto 					instance = get_instance();

	if (get_instance()->get_state() == state::deinitialized)
		return;

	bool						is_landscape_and_decorations_generated =
	(
		instance->have_worker(chunk) and
		instance->find_worker(chunk).get_status() >= chunk_generation_worker::generated_decorations
	);

	const auto					&old_worker = find_worker(chunk);

	debug::check
	(
		not old_worker.is_busy(),
		"[game::chunk_generation_director] Old worker haven't finish its work, but a new worker is created. This may cause artifacts"
	);

	instance->drop_worker(chunk);

	auto						&new_worker = instance->find_or_create_worker(chunk, is_landscape_and_decorations_generated);

	old_worker.share_workspace(new_worker);
	new_worker.process(true);
}

void 							chunk_generation_director::delete_build(const shared_ptr<chunk> &chunk)
{
	if (get_instance()->get_state() == state::deinitialized)
		return;

	get_instance()->drop_worker(chunk);
}

bool							chunk_generation_director::have_worker(const shared_ptr<chunk> &chunk)
{
	const auto 					instance = get_instance();

	return instance->active_workers.find(chunk) != instance->active_workers.end();
}

chunk_generation_worker			&chunk_generation_director::find_worker(const shared_ptr<chunk> &chunk)
{
	return *get_instance()->active_workers.at(chunk);
}

chunk_generation_worker			&chunk_generation_director::find_or_create_worker
								(
									const shared_ptr<chunk> &chunk,
									bool preserve_landscape_and_decorations
								)
{
	const auto 					instance = get_instance();

	if (instance->active_workers.find(chunk) == instance->active_workers.end())
		instance->active_workers.emplace(chunk, make_unique<chunk_generation_worker>(chunk, not preserve_landscape_and_decorations));

	return *instance->active_workers.at(chunk);
}

void 							chunk_generation_director::when_deinitialized()
{
#if FT_VOX_FORCE_EXIT
	return;
#endif

	for (const auto &worker : dropped_workers)
		worker->wait_for_finish_of_task();

	for (const auto &[chunk, worker] : active_workers)
		worker->wait_for_finish_of_task();
}

void 							chunk_generation_director::when_updated()
{
	for (auto iterator = dropped_workers.begin(); iterator != dropped_workers.end();)
	{
		if (not (*iterator)->is_busy())
			iterator = dropped_workers.erase(iterator);
		else
			++iterator;
	}
}

void 							chunk_generation_director::drop_worker(const shared_ptr<chunk> &chunk)
{
	if (auto iterator = active_workers.find(chunk); iterator != active_workers.end())
	{
		iterator->second->stop_workflow();
		dropped_workers.push_back(move(iterator->second));
		active_workers.erase(iterator);
	}
}