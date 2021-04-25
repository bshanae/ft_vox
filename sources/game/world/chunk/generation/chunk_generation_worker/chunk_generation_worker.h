#pragma once

#include "application/common/imports/std.h"
#include "application/common/imports/glm.h"
#include "application/common/templates/notifier_and_listener/listener.h"

#include "game/world/chunk/generation/utilities/chunk_build/chunk_build.h"
#include "game/world/chunk/generation/chunk_generation_task/notifications/chunk_generation_task_notification.h"

namespace								game
{
	class								chunk;
	class								chunk_workspace;
	class								chunk_generation_task;

	class								chunk_generation_worker;
}

class									game::chunk_generation_worker final :
											public listener<game::chunk_generation_task_notification>
{
public :

	enum								generation_status
	{
		null,
		generated_landscape,
		generated_decorations,
		generated_light,
		generated_geometry,
		generated_model
	};

	explicit							chunk_generation_worker
										(
											const shared_ptr<chunk> &chunk,
											bool generate_landscape_and_decorations = true
										);
										~chunk_generation_worker() = default;

	generation_status					get_status() const;
	bool 								is_busy() const;

	optional<chunk_build>				process(bool try_build_at_once = false);

	/// Tells worker not to execute new task. However, worker still waits for end of active task
	void 								stop_workflow();

	void								share_workspace(chunk_generation_worker &target) const;

private :

	static constexpr float				processing_limit = 10.f / 60.f;

	bool 								is_workflow_stopped;
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

	void 								unset_task();
	void 								set_task(chunk_generation_task *task);

	bool								can_launch_decoration_generation_task() const;
	bool								can_launch_geometry_generation_task() const;
};