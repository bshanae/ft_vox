#include "chunk_light_builder.h"

#include "game/world/chunk/block/block/block_settings.h"
#include "game/world/chunk/block/block_pointer/block_pointer.h"
#include "game/world/chunk/chunk/building/chunk_workspace/chunk_workspace.h"

using namespace					game;

constexpr float 				lowest_light_level_for_recursion = 0.1f;
constexpr float 				light_level_delta = 0.15f;

void							chunk_light_builder::launch(const shared_ptr<chunk_workspace> &workspace)
{
	debug::check_critical
	(
		workspace->state == chunk_workspace::nothing_done,
		"[chunk_light_builder] Chunk workspace has unexpected state"
	);

	workspace->state = chunk_workspace::light_in_process;
	workspace->light_build_future = async(launch::async, &do_launch, workspace);
}

void							chunk_light_builder::do_launch(const shared_ptr<chunk_workspace> &workspace)
{
	initialize_light(workspace);
	spread_light(workspace);

	workspace->state = chunk_workspace::light_done;
}

void							chunk_light_builder::initialize_light(const shared_ptr<chunk_workspace> &workspace)
{
	chunk::index				index;

	for (index.x = 0; index.x < chunk_settings::size[0]; index.x++)
	for (index.y = 0; index.y < chunk_settings::size[1]; index.y++)
	for (index.z = 0; index.z < chunk_settings::size[2]; index.z++)
	{
		if (index.y == chunk_settings::size[1] - 1)
			workspace->chunk->at(index).set_light_level(block_settings::sun_light);
		else
			workspace->chunk->at(index).set_light_level(0.f);
	}
}

void							chunk_light_builder::spread_light(const shared_ptr<chunk_workspace> &workspace)
{
	chunk::index				index;
	vector<chunk::index>		lighted_blocks;

	for (index.y = chunk_settings::size[1] - 2; index.y >= 0; index.y--)
	{
		spread_light_straight_down(workspace, lighted_blocks, index.y);
		spread_light_in_all_directions(workspace, lighted_blocks);
		lighted_blocks.clear();
	}
}

void							chunk_light_builder::spread_light_straight_down
								(
									const shared_ptr<chunk_workspace> &workspace,
									vector<chunk::index> &lighted_blocks,
									int y
								)
{
	chunk::index				index;

	index.y = y;
	for (index.x = 0; index.x < chunk_settings::size[0]; index.x++)
	for (index.z = 0; index.z < chunk_settings::size[2]; index.z++)
	{
		block					&block = workspace->chunk->at(index);

		if (does_transmit_light(get_meta_type(block.get_type())))
		{
			game::block			&upper_neighbor = workspace->chunk->at(index.x, index.y + 1, index.z);

			block.set_light_level(upper_neighbor.get_light_level());
			lighted_blocks.push_back(index);
		}
	}
}

void 							chunk_light_builder::spread_light_in_all_directions
								(
									const shared_ptr<chunk_workspace> &workspace,
									vector<chunk::index> &lighted_blocks
								)
{
	for (const chunk::index &index : lighted_blocks)
		spread_light_in_all_directions_from_block(workspace, block_pointer(workspace->chunk, index));
}

void							chunk_light_builder::spread_light_in_all_directions_from_block
								(
									const shared_ptr<chunk_workspace> &workspace,
									const block_pointer &block
								)
{
	static const chunk::index	offsets[] =
	{
		chunk::index(-1, 0, 0),
		chunk::index(+1, 0, 0),

		chunk::index(0, +1, 0),

		chunk::index(0, 0, -1),
		chunk::index(0, 0, +1)
	};

	const float				light_level = block->get_light_level();
	block_pointer			neighbor;

	if (light_level <= lowest_light_level_for_recursion)
		return;

	for (const auto &offset : offsets)
	{
		if (neighbor = block.get_neighbor(offset); neighbor)
		{
			if (!does_transmit_light(get_meta_type(neighbor->get_type())))
				continue;
			if (neighbor->get_light_level() >= light_level)
				continue;

			neighbor->set_light_level(light_level - light_level_delta);
			spread_light_in_all_directions_from_block(workspace, neighbor);
		}
	}
}