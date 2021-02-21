#pragma once

#include "application/common/templates/singleton/singleton.h"

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

	static bool		should_build_quad
					(
						const shared_ptr<chunk_workspace> &workspace,
						chunk_workspace::batch &batch,
						const block_pointer &this_block_pointer,
						const block_pointer &neighbor_block_pointer
					);

	static void		build_quad
					(
						const shared_ptr<chunk_workspace> &workspace,
						chunk_workspace::batch &batch,
						const block &this_block,
						const chunk::index &index,
						axis axis,
						sign sign,
						float light_level
					);

	template		<typename type>
	static void		append_to_vector(vector<type> &target, const vector<type> &source);

	static void		calculate_ao_for_quad
					(
						const block_pointer &block,
						const chunk::index (&occluders_offsets)[4][3],
						float (&ao_levels)[4]
					);

	static float	calculate_ao_for_vertex
					(
						const block_pointer &block,
						const chunk::index (&occluders_offsets)[3]
					);

	static float	combine_light_and_ao(float light, float ao);
};


