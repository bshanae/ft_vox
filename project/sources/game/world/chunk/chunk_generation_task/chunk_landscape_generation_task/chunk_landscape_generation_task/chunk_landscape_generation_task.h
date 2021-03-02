#pragma once

#include "game/world/chunk/chunk_generation_task/chunk_generation_task/chunk_generation_task.h"

namespace			game
{
	class			chunk_landscape_generation_task;
}

class				game::chunk_landscape_generation_task : public game::chunk_generation_task
{
public :
					chunk_landscape_generation_task();
					~chunk_landscape_generation_task() override = default;
protected :

	void 			do_launch(chunk_workspace &workspace) override;
};