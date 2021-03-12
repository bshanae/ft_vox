#include "chunk_generation_worker.h"

#include "application/common/utilities/type_utility.h"

#include "engine/main/system/time/timer/timer.h"

#include "game/world/chunk/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/chunk_generation_task/notifications/chunk_generation_task_launched.h"
#include "game/world/chunk/chunk_generation_task/notifications/chunk_generation_task_done.h"
#include "game/world/chunk/chunk_generation_task/chunk_generation_task/chunk_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generation_task/chunk_landscape_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_light_generation_task/chunk_light_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_model_generation_task/chunk_model_generation_task.h"
#include "game/world/chunk/chunk_generation_director/chunk_generation_director.h"
#include "game/world/world/world.h"

using namespace			game;

using					generation_status = chunk_generation_worker::generation_status;

						chunk_generation_worker::chunk_generation_worker
						(
							const shared_ptr<chunk> &chunk,
							bool generate_landscape
						) :
							is_workflow_stopped(false),
							should_switch_task(true),
							status(generate_landscape ? null : generated_landscape),
							next_status(generate_landscape ? null : generated_landscape)
{
	workspace = make_unique<chunk_workspace>(chunk);
}

generation_status					chunk_generation_worker::get_status() const
{
	return status;
}

optional<chunk_build>	chunk_generation_worker::process(bool try_build_at_once)
{
	engine::timer		timer{ processing_limit };

	while (true)
	{
		switch_task_if_needed();
		launch_task_if_needed();

		if (is_build_ready())
			return { package_build() };

		if (timer.did_finish())
			break;
		if (not try_build_at_once)
			break;
	}

	return nullopt;
}

void 					chunk_generation_worker::stop_workflow()
{
	is_workflow_stopped = true;
}

bool 					chunk_generation_worker::is_busy() const
{
	return task != nullptr and task->get_state() == chunk_generation_task::launched;
}

void					chunk_generation_worker::when_notified(const chunk_generation_task_notification &notification)
{
	if (type_utility::is_of_type<chunk_generation_task_done>(notification))
	{
		status = next_status;
		should_switch_task = true;
	}
}

bool 					chunk_generation_worker::is_build_ready() const
{
	return status == generation_status::generated_model;
}

chunk_build				chunk_generation_worker::package_build() const
{
	chunk_build         chunkBuild;

	chunkBuild.model_for_opaque = workspace->batch_for_opaque.model;
    chunkBuild.model_for_transparent = workspace->batch_for_transparent.model;
    chunkBuild.model_for_partially_transparent = workspace->batch_for_partially_transparent.model;

	return chunkBuild;
}

void					chunk_generation_worker::switch_task_if_needed()
{
	if (is_workflow_stopped)
		return;

	if (should_switch_task)
		switch_task();
}

void					chunk_generation_worker::switch_task()
{
	if (task != nullptr)
		unset_task();

	switch (status)
	{
		case generation_status::null:
		{
			set_task(new chunk_landscape_generation_task());
			next_status = generation_status::generated_landscape;
			should_switch_task = false;
			break;
		}

		case generation_status::generated_landscape:
		{
			set_task(new chunk_light_generation_task());
			next_status = generation_status::generated_light;
			should_switch_task = false;
			break;
		}

		case generation_status::generated_light:
		{
			if (not can_launch_geometry_generation_task())
				break;

			set_task(new chunk_geometry_generation_task());
			next_status = generation_status::generated_geometry;
			should_switch_task = false;
			break;
		}

		case generation_status::generated_geometry:
		{
			set_task(new chunk_model_generation_task());
			next_status = generation_status::generated_model;
			should_switch_task = false;
			break;
		}

		case generation_status::generated_model:
			break;

		default:
		{
			debug::raise_warning("[game::chunk_generation_worker] Unexpected task state");
			break;
		}
	}
}

void 					chunk_generation_worker::launch_task_if_needed()
{
	if (is_workflow_stopped)
		return;

	if (task != nullptr and task->get_state() == chunk_generation_task::state::deferred)
		launch_task();
}

void 					chunk_generation_worker::launch_task()
{
	task->launch(*workspace);
}

void 					chunk_generation_worker::unset_task()
{
#if FT_VOX_DEBUG
	task->check_number_of_listeners(1);
	debug::check_critical(task->get_state() == chunk_generation_task::state::done, "[chunk_generation_worker] Task is not done");
#endif

	task->unsubscribe(*this);
	task = nullptr;
}

void 					chunk_generation_worker::set_task(chunk_generation_task *task)
{
	this->task = unique_ptr<chunk_generation_task>(task);
	this->task->subscribe(*this);
}

bool 					chunk_generation_worker::can_launch_geometry_generation_task() const
{
	static const auto	did_worker_generate_light = [](const chunk_generation_worker &worker)
	{
		return worker.get_status() >= generation_status::generated_light;
	};

	static const auto	is_worker_present_and_generated_light = [](const vec3 &position_of_chunk)
	{
		if (auto chunk = world::find_chunk(position_of_chunk); chunk != nullptr)
		{
			if (chunk_generation_director::have_worker(chunk))
				return did_worker_generate_light(chunk_generation_director::find_worker(chunk));
		}

		return false;
	};

	return
	(
		is_worker_present_and_generated_light(workspace->chunk->get_position() + chunk::left_offset) and
		is_worker_present_and_generated_light(workspace->chunk->get_position() + chunk::right_offset) and
		is_worker_present_and_generated_light(workspace->chunk->get_position() + chunk::forward_offset) and
		is_worker_present_and_generated_light(workspace->chunk->get_position() + chunk::back_offset)
	);
}