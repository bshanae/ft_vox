#include "chunk_light_builder.h"

#include "game/world/chunk/chunk/building/chunk_workspace/chunk_workspace.h"

using namespace		game;

void				chunk_light_builder::launch(const shared_ptr<chunk_workspace> &workspace)
{
	debug::check_critical
	(
		workspace->state == chunk_workspace::nothing_done,
		"[chunk_light_builder] Chunk workspace has unexpected state"
	);

	workspace->state = chunk_workspace::light_in_process;
	workspace->light_build_future = async(launch::async, &do_launch, workspace);
}

void				chunk_light_builder::do_launch(const shared_ptr<chunk_workspace> &workspace)
{
	workspace->state = chunk_workspace::light_done;
}