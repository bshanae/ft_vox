#pragma once

#include "application/common/templates/singleton/singleton.h"

#include "game/world/chunk/chunk/chunk/chunk.h"
#include "game/world/chunk/chunk/building/chunk_workspace/chunk_workspace.h"

namespace			game
{
	class			block;
	class			chunk_geometry_builder;
}

class				game::chunk_geometry_builder : public singleton<game::chunk_geometry_builder>
{
public :
					chunk_geometry_builder() = default;
					~chunk_geometry_builder() override = default;

	static void		launch(const shared_ptr<chunk_workspace> &workspace);
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
						const chunk::index &index,
						axis axis,
						sign sign
					);

	static void		build_quad
					(
						const shared_ptr<chunk_workspace> &workspace,
						chunk_workspace::batch &batch,
						const chunk::index &index,
						axis axis,
						sign sign
					);

	template		<typename type>
	static void		append_to_vector(vector<type> &target, const vector<type> &source);
};


