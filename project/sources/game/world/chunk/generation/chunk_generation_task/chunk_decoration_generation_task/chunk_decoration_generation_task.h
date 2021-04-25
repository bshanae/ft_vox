#pragma once

#include "application/common/imports/glm.h"
#include "game/world/chunk/chunk/chunk.h"
#include "game/world/chunk/generation/chunk_generation_task/chunk_generation_task/chunk_generation_task.h"

namespace			game
{
	class			chunk_decoration_generation_task;
}

class				game::chunk_decoration_generation_task : public game::chunk_generation_task
{
public :
					chunk_decoration_generation_task();
					~chunk_decoration_generation_task() override = default;
protected :

	void 			do_launch(chunk_workspace &workspace) override;

	static void		generate_decoration_on_chunk(chunk_workspace &workspace);
	static void		generate_decoration_on_column(chunk_workspace &workspace, chunk::index index);
};