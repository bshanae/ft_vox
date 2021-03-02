#pragma once

#include "application/common/imports/std.h"

#include "game/world/chunk/chunk_build/chunk_build.h"

namespace								game
{
	class								chunk;
	class								chunk_workspace;
	class								chunk_generation_task;

	class								chunk_generation_worker;
}

class									game::chunk_generation_worker final
{
public :

	explicit							chunk_generation_worker(const shared_ptr<chunk> &chunk);
										~chunk_generation_worker() = default;

	optional<chunk_build>				process(bool try_build_at_once = false);
	bool 								is_busy() const;

private :

	static constexpr float				processing_limit = 10.f / 60.f;

	shared_ptr<chunk_workspace>			workspace;
	unique_ptr<chunk_generation_task>	task;

	bool 								is_build_ready() const;
	chunk_build							package_build() const;

	void								go_to_next_task_if_needed();
	void								go_to_next_task();

	void 								launch_task_if_needed();
	void 								launch_task();
};