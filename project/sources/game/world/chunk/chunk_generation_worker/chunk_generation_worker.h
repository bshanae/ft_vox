#pragma once

#include "application/common/imports/std.h"
#include "application/common/templates/notifier_and_listener/listener.h"

#include "game/world/chunk/chunk_build/chunk_build.h"
#include "game/world/chunk/chunk_generation_task/notifications/chunk_generation_task_notification.h"

namespace								game
{
	class								chunk;
	class								chunk_workspace;
	class								chunk_generation_task;

	class								chunk_generation_worker;
}

class									game::chunk_generation_worker final :
											public enable_shared_from_this<game::chunk_generation_worker>,
											public listener<game::chunk_generation_task_notification>
{
public :

	enum								generation_status
	{
		nothing_generated,
		landscape_generated,
		light_generated,
		geometry_generated,
		model_generated
	};

	explicit							chunk_generation_worker(const shared_ptr<chunk> &chunk);
										~chunk_generation_worker() = default;

	generation_status					get_status() const;
	bool 								is_busy() const;

	optional<chunk_build>				process(bool try_build_at_once = false);

private :

	static constexpr float				processing_limit = 10.f / 60.f;

	unique_ptr<chunk_workspace>			workspace;
	unique_ptr<chunk_generation_task>	task;

	generation_status					status;
	generation_status					next_status;
	bool 								should_switch_task;

	void								when_notified(const chunk_generation_task_notification &notification) override;

	bool 								is_build_ready() const;
	chunk_build							package_build() const;

	void								switch_task_if_needed();
	void								switch_task();

	void 								launch_task_if_needed();
	void 								launch_task();
};