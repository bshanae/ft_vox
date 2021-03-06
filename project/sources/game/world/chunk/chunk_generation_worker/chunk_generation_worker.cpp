#include "chunk_generation_worker.h"

#include "application/common/utilities/type_utility.h"
#include "application/common/utilities/enum_utility.h"

#include "engine/main/system/time/timer/timer.h"

#include "game/world/chunk/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/chunk_generation_task/notifications/chunk_generation_task_launched.h"
#include "game/world/chunk/chunk_generation_task/notifications/chunk_generation_task_done.h"
#include "game/world/chunk/chunk_generation_task/chunk_generation_task/chunk_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generation_task/chunk_landscape_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_light_generation_task/chunk_light_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task/chunk_geometry_generation_task.h"
#include "game/world/chunk/chunk_generation_task/chunk_model_generation_task/chunk_model_generation_task.h"

using namespace			game;

using					generation_status = chunk_generation_worker::generation_status;

						chunk_generation_worker::chunk_generation_worker(const shared_ptr<chunk> &chunk) :
							should_switch_task(true),
							status(generation_status::nothing_generated),
							next_status(generation_status::nothing_generated)
{
	workspace = make_unique<chunk_workspace>(chunk);
}

generation_status		chunk_generation_worker::get_status() const
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

bool 					chunk_generation_worker::is_busy() const
{
	// TODO Fix this - Stop work when asked
	return not is_build_ready();
}

void					chunk_generation_worker::when_notified(const chunk_generation_task_notification &notification)
{
	if (type_utility::check_type<chunk_generation_task_done>(notification))
	{
		status = next_status;
		should_switch_task = true;
	}
}

bool 					chunk_generation_worker::is_build_ready() const
{
	return status == generation_status::model_generated;
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

void					chunk_generation_worker::switch_task_if_needed()
{
	if (should_switch_task)
		switch_task();
}

void					chunk_generation_worker::switch_task()
{
#if FT_VOX_DEBUG
	if (task != nullptr)
		task->check_number_of_listeners(1);
#endif

	if (task != nullptr)
		task->unsubscribe(*this);

	switch (status)
	{
		case generation_status::nothing_generated:
			task = unique_ptr<chunk_generation_task>(new chunk_landscape_generation_task());
			next_status = generation_status::landscape_generated;
			break;

		case generation_status::landscape_generated:
			task = unique_ptr<chunk_generation_task>(new chunk_light_generation_task());
			next_status = generation_status::light_generated;
			break;

		case generation_status::light_generated:
			task = unique_ptr<chunk_generation_task>(new chunk_geometry_generation_task());
			next_status = generation_status::geometry_generated;
			break;

		case generation_status::geometry_generated:
			task = unique_ptr<chunk_generation_task>(new chunk_model_generation_task());
			next_status = generation_status::model_generated;
			break;

		case generation_status::model_generated:
			break;

		default:
			debug::raise_warning("[game::chunk_generation_worker] Unexpected task state");
			break;
	}

	should_switch_task = false;

#if FT_VOX_DEBUG
	if (task != nullptr)
		task->check_number_of_listeners(0);
#endif

	if (task != nullptr)
		task->subscribe(*this);
}

void 					chunk_generation_worker::launch_task_if_needed()
{
	if (task != nullptr and task->get_state() == chunk_generation_task::state::deferred)
		launch_task();
}

void 					chunk_generation_worker::launch_task()
{
	task->launch(*workspace);
}