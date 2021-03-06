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

	return instance->find_or_create_worker(chunk).process();
}

void							chunk_generation_director::reset_build(const shared_ptr<chunk> &chunk)
{
	const auto 					instance = get_instance();

	if (get_instance()->get_state() == state::deinitialized)
		return;

	instance->drop_worker(chunk);
	instance->find_or_create_worker(chunk).process(true);
}

void 							chunk_generation_director::delete_build(const shared_ptr<chunk> &chunk)
{
	if (get_instance()->get_state() == state::deinitialized)
		return;

	get_instance()->drop_worker(chunk);
}

bool							chunk_generation_director::have_worker(const shared_ptr<chunk> &chunk)
{
	return get_instance()->active_workers.contains(chunk);
}

const chunk_generation_worker	&chunk_generation_director::find_worker(const shared_ptr<chunk> &chunk)
{
	return *get_instance()->active_workers.at(chunk);
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
	erase_if
	(
		dropped_workers,
		[](const unique_ptr<chunk_generation_worker> &worker){ return not worker->is_busy(); }
	);
}
chunk_generation_worker			&chunk_generation_director::find_or_create_worker(const shared_ptr<chunk> &chunk)
{
	if (not active_workers.contains(chunk))
		active_workers.emplace(chunk, make_unique<chunk_generation_worker>(chunk));

	return *active_workers.at(chunk);
}

void 							chunk_generation_director::drop_worker(const shared_ptr<chunk> &chunk)
{
	if (auto iterator = active_workers.find(chunk); iterator != active_workers.end())
	{
		dropped_workers.push_back(move(iterator->second));
		active_workers.erase(iterator);
	}
}