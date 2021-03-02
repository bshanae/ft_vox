#pragma once

#include "game/world/chunk/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/chunk_generation_task/chunk_generation_task/chunk_generation_task.h"

namespace			game
{
	class			chunk_model_generation_task;
}

class				game::chunk_model_generation_task : public game::chunk_generation_task
{
public :
					chunk_model_generation_task();
					~chunk_model_generation_task() override = default;
protected :

	void 			do_launch(chunk_workspace &workspace) override;

private :

	static void		process_batch(chunk_workspace &workspace, chunk_workspace::batch &batch);
};