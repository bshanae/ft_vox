#pragma once

#include "application/common/templates/singleton/singleton.h"

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

#include "game/world/chunk/chunk_generation_worker/chunk_generation_worker.h"
#include "game/world/chunk/chunk_workspace/chunk_workspace.h"

namespace							game
{
	class							chunk_build;
	class							chunk_generation_director;
}

class								game::chunk_generation_director :
										public engine::object,
										public engine::unique_object_constructor<game::chunk_generation_director>
{
public :
									chunk_generation_director();
									~chunk_generation_director() override = default;

	static optional<chunk_build>	process_build(const shared_ptr<chunk> &chunk);
	static void 					reset_build(const shared_ptr<chunk> &chunk);
	static void 					delete_build(const shared_ptr<chunk> &chunk);

private :

	using							worker_ptr = shared_ptr<chunk_generation_worker>;
	using							workers_map = unordered_map<shared_ptr<chunk>, worker_ptr>;
	using							workers_list = list<worker_ptr>;

	workers_map						active_workers;
	workers_list					dropped_workers;

	void 							when_deinitialized() override;
	void 							when_updated() override;

	worker_ptr						get_or_create_worker(const shared_ptr<chunk> &chunk);
	void 							drop_worker(const shared_ptr<chunk> &chunk);

	static bool						is_chunk_present_and_has_light(const vec3 &position);
	static bool						are_all_neighbors_present_and_have_light(const shared_ptr<chunk> &chunk);
};


