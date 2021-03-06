#include "chunk_generation_task.h"

#include "application/common/debug/debug.h"

#include "game/world/chunk/chunk_generation_task/notifications/chunk_generation_task_launched.h"
#include "game/world/chunk/chunk_generation_task/notifications/chunk_generation_task_done.h"

using namespace				game;

using						state = enum chunk_generation_task::state;

							chunk_generation_task::~chunk_generation_task()
{
	wait();
}

state						chunk_generation_task::get_state() const
{
	return state;
}

void 						chunk_generation_task::launch(chunk_workspace &workspace)
{
#if FT_VOX_DEBUG
	debug::check_critical(state == state::deferred, "[game::chunk_generation_task] Unexpected state");
#endif

	state = launched;

	if (is_async)
	{
		future = async
		(
			launch::async,
			[this, &workspace]()
			{
				notify(chunk_generation_task_launched());
				do_launch(workspace);
				state = done;
				notify(chunk_generation_task_done());
			}
		);
	}
	else
	{
		notify(chunk_generation_task_launched());
		do_launch(workspace);
		state = done;
		notify(chunk_generation_task_done());
	}
}

void 						chunk_generation_task::wait()
{
	if (future)
		future->wait();
}

							chunk_generation_task::chunk_generation_task(bool is_async) : is_async(is_async)
{
	state = deferred;
}