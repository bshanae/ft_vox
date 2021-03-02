#include "chunk_generation_worker.h"

#include "engine/main/system/time/timer/timer.h"

#include "game/world/chunk/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/chunk_generation_task/chunk_generation_task/chunk_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generation_task/chunk_landscape_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_light_generation_task/chunk_light_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_model_generation_task/chunk_model_generation_task.h"

using namespace			game;

static const auto		landscape_generation_task_type_hash = typeid(const chunk_landscape_generation_task &).hash_code();
static const auto		light_generation_task_type_hash = typeid(const chunk_light_generation_task &).hash_code();
static const auto		geometry_generation_task_type_hash = typeid(const chunk_geometry_generation_task &).hash_code();
static const auto		model_generation_task_type_hash = typeid(const chunk_model_generation_task &).hash_code();

						chunk_generation_worker::chunk_generation_worker(const shared_ptr<chunk> &chunk) :
							workspace(),
							task()
{
	workspace = make_shared<chunk_workspace>(chunk);
}

optional<chunk_build>	chunk_generation_worker::process(bool try_build_at_once)
{
	engine::timer		timer{ processing_limit };

	do
	{
		if (timer.did_finish())
			break;

		go_to_next_task_if_needed();
		launch_task_if_needed();

		if (is_build_ready())
			return { package_build() };
	}
	while (try_build_at_once);

	return nullopt;
}

bool 					chunk_generation_worker::is_busy() const
{
	return task != nullptr and task->is_processing();
}

bool 					chunk_generation_worker::is_build_ready() const
{
	return
	(
		workspace->batch_for_opaque.model != nullptr &&
		workspace->batch_for_transparent.model != nullptr &&
		workspace->batch_for_partially_transparent.model != nullptr
	);
}

chunk_build				chunk_generation_worker::package_build() const
{
	return
	{
		.model_for_opaque = workspace->batch_for_opaque.model,
		.model_for_transparent = workspace->batch_for_transparent.model,
		.model_for_partially_transparent = workspace->batch_for_partially_transparent.model
	};
}

void					chunk_generation_worker::go_to_next_task_if_needed()
{
	if (task == nullptr or task->is_finished())
		go_to_next_task();
}

void					chunk_generation_worker::go_to_next_task()
{
	if (task == nullptr)
	{
		task = unique_ptr<chunk_generation_task>(new chunk_landscape_generation_task());
	}
	else
	{
		const auto		&task_ref = *task;
		const auto		task_type_hash = typeid(task_ref).hash_code();

		if (task_type_hash == landscape_generation_task_type_hash)
			task = unique_ptr<chunk_generation_task>(new chunk_light_generation_task());
		else if (task_type_hash == light_generation_task_type_hash)
			task = unique_ptr<chunk_generation_task>(new chunk_geometry_generation_task());
		else if (task_type_hash == geometry_generation_task_type_hash)
			task = unique_ptr<chunk_generation_task>(new chunk_model_generation_task());
		else if (task_type_hash == model_generation_task_type_hash)
			;
		else
			debug::raise_warning("[game::chunk_generation_worker] Unexpected task state");
	}
}

void 					chunk_generation_worker::launch_task_if_needed()
{
	if (task != nullptr and task->is_waiting())
		launch_task();
}

void 					chunk_generation_worker::launch_task()
{
	task->launch(*workspace);
}