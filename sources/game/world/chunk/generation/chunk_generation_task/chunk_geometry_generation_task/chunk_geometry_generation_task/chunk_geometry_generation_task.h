#pragma once

#include "game/world/block/block_ptr/block_ptr.h"
#include "game/world/chunk/generation/utilities/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/generation/chunk_generation_task/chunk_generation_task/chunk_generation_task.h"
#include "game/world/chunk/chunk/chunk.h"

namespace			game
{
	class			chunk_geometry_generation_task;
}

class				game::chunk_geometry_generation_task : public game::chunk_generation_task
{
public :
					chunk_geometry_generation_task();
					~chunk_geometry_generation_task() override = default;
protected :

	void 			do_launch(chunk_workspace &workspace) override;

private :

	static void 	filter_blocks_and_save_to_batches(chunk_workspace &workspace);
	static void 	launch_batches_processing(chunk_workspace &workspace);

	static void 	process_batch(chunk_workspace::batch &batch);
	static void		process_block(chunk_workspace::batch &batch, const block_ptr &block);

	static bool		should_generate_quad(chunk_workspace::batch &batch,const block_ptr &this_block, const block_ptr &neighbor_block);
	static void 	generate_quad(chunk_workspace::batch &batch, const block_ptr &block, block_face face, float light_level);

	static void		generate_indices(chunk_workspace::batch &batch);
	static void		generate_vertices(chunk_workspace::batch &batch, const block_ptr &block, block_face face);
	static void		generate_texture_coordinates(chunk_workspace::batch &batch, const block_ptr &block, block_face face);
	static void		generate_light_levels(chunk_workspace::batch &batch, const block_ptr &block, block_face face, float light_level);
};