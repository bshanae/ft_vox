#pragma once

#include "game/world/chunk/chunk/chunk.h"
#include "game/world/chunk/chunk_generation_task/chunk_generation_task/chunk_generation_task.h"

namespace			game
{
	class			chunk_light_generation_task;
}

class				game::chunk_light_generation_task : public game::chunk_generation_task
{
public :
					chunk_light_generation_task();
					~chunk_light_generation_task() override = default;
protected :

	void 			do_launch(chunk_workspace &workspace) override;

private :

	static void		initialize_light(const chunk_workspace &workspace);
	static void		spread_light(const chunk_workspace &workspace);

	static void		spread_light_straight_down
					(
						const chunk_workspace &workspace,
						vector<chunk::index> &lighted_blocks,
						int y
					);

	static void		spread_light_in_all_directions
					(
						const chunk_workspace &workspace,
						vector<chunk::index> &lighted_blocks
					);

	static void		spread_light_in_all_directions_from_block
					(
						const chunk_workspace &workspace,
						const block_ptr &block
					);
};