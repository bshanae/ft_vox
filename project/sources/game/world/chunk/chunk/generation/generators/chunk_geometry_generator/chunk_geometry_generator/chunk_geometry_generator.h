#pragma once

#include "application/common/templates/singleton/singleton.h"

#include "game/world/chunk/block/block_face/block_face.h"
#include "game/world/chunk/chunk/chunk/chunk.h"
#include "game/world/chunk/chunk/generation/chunk_workspace/chunk_workspace.h"

namespace			game
{
	class			block;
	class			chunk_geometry_generator;
}

class				game::chunk_geometry_generator : public singleton<game::chunk_geometry_generator>
{
public :
					chunk_geometry_generator() = default;
					~chunk_geometry_generator() override = default;

	static void		process(const shared_ptr<chunk_workspace> &workspace);
	static void		wait(const shared_ptr<chunk_workspace> &workspace);

private :

	static bool		filter_for_opaque(const block &block);
	static bool		filter_for_transparent(const block &block);
	static bool		filter_for_partially_transparent(const block &block);

	static void 	process_batch
					(
						shared_ptr<chunk_workspace> workspace,
						chunk_workspace::batch &batch
					);

	static void		process_block
					(
						const shared_ptr<chunk_workspace> &workspace,
						chunk_workspace::batch &batch,
						const chunk::index &index
					);

	static bool		should_generate_quad
					(
						chunk_workspace::batch &batch,
						const block_pointer &this_block_pointer,
						const block_pointer &neighbor_block_pointer
					);

	static void 	generate_quad
					(
						chunk_workspace::batch &batch,
						const block_pointer &block,
						block_face face,
						float light_level
					);

	static void		generate_indices(chunk_workspace::batch &batch);

	static void		generate_vertices
					(
						chunk_workspace::batch &batch,
						const block_pointer &block,
						block_face face
					);

	static void 	generate_texture_coordinates
					(
						chunk_workspace::batch &batch,
						const block_pointer &block,
						block_face face
					);

	static void 	generate_light_levels
					(
						chunk_workspace::batch &batch,
						const block_pointer &block,
						block_face face,
						float light_level
					);
};

