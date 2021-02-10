#pragma once

#include "application/common/templates/singleton/singleton.h"

#include "game/world/chunk/chunk/chunk/chunk.h"

namespace					game
{
	class					chunk_workspace;
	class					chunk_light_builder;
}

class						game::chunk_light_builder : public singleton<game::chunk_light_builder>
{
public :
							chunk_light_builder() = default;
							~chunk_light_builder() override = default;

	static void				launch(const shared_ptr<chunk_workspace> &workspace);

private :

	static void 			do_launch(const shared_ptr<chunk_workspace> &workspace);

	static void				initialize_light(const shared_ptr<chunk_workspace> &workspace);
	static void				spread_light(const shared_ptr<chunk_workspace> &workspace);

	static void				spread_light_straight_down
							(
								const shared_ptr<chunk_workspace> &workspace,
								vector<chunk::index> &lighted_blocks,
								int y
							);

	static void				spread_light_in_all_directions
							(
								const shared_ptr<chunk_workspace> &workspace,
								vector<chunk::index> &lighted_blocks
							);

	static void				spread_light_in_all_directions_from_block
							(
								const shared_ptr<chunk_workspace> &workspace,
								const chunk::index &index
							);
};
