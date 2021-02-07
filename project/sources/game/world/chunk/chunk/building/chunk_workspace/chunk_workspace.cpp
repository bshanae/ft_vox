#include "chunk_workspace.h"

using namespace				game;

							chunk_workspace::chunk_workspace(const shared_ptr<game::chunk> &chunk) :
								chunk(chunk),
								state(nothing_done),
								build_at_once(false)
{}

void						chunk_workspace::reset()
{
	auto 					reset_batch = [](batch &batch)
	{
		batch.filter = nullptr;

		batch.geometry_future.reset();

		batch.vertices.clear();
		batch.texture_coordinates.clear();
		batch.light_levels.clear();
		batch.indices.clear();

		batch.model = nullptr;
	};

	state = nothing_done;

	reset_batch(batch_for_opaque);
	reset_batch(batch_for_transparent);
	reset_batch(batch_for_partially_transparent);
}