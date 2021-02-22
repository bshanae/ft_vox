#include "chunk_workspace.h"

using namespace				game;

							chunk_workspace::chunk_workspace(const shared_ptr<game::chunk> &chunk) :
								chunk(chunk),
								state(nothing_done),
								build_at_once(false)
{}

void 						chunk_workspace::wait()
{
	switch (state)
	{
		case light_in_process:
			light_build_future->wait();
			break;

		case geometry_in_process:
			batch_for_opaque.geometry_future->wait();
			batch_for_transparent.geometry_future->wait();
			batch_for_partially_transparent.geometry_future->wait();
			break;

		default:
			break;
	}
}

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

	state = landscape_done;

	landscape_future.reset();
	light_build_future.reset();

	reset_batch(batch_for_opaque);
	reset_batch(batch_for_transparent);
	reset_batch(batch_for_partially_transparent);
}