#pragma once

#include "application/common/imports/std.h"
#include "application/common/templates/notifier_and_listener/notifier.h"

#include "game/world/chunk/chunk_generation_task/notifications/chunk_generation_task_notification.h"

namespace					game
{
	class					chunk_workspace;
	class					chunk_generation_task;
}

class						game::chunk_generation_task : public notifier<game::chunk_generation_task_notification>
{
public :

	enum					state
	{
		deferred,
		launched,
		done
	};

							chunk_generation_task() = delete;
	virtual					~chunk_generation_task();

	state					get_state() const;

	void 					launch(chunk_workspace &workspace);
	void 					wait();

protected :

	explicit				chunk_generation_task(bool is_async);
	virtual void 			do_launch(chunk_workspace &workspace) = 0;

private :

	const bool 				is_async;
	enum state				state;
	optional<future<void>>	future;
};


