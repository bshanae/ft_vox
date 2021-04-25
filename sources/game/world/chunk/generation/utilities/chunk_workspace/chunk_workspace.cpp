#include "chunk_workspace.h"

using namespace				game;

							chunk_workspace::chunk_workspace(const shared_ptr<game::chunk> &chunk) : chunk(chunk)
{}

							chunk_workspace::~chunk_workspace()
{
	static const auto		wait_for_future_if_it_is_present = [](const optional<future<void>> &future)
	{
		if (future)
			future->wait();
	};

	wait_for_future_if_it_is_present(landscape_future);
	wait_for_future_if_it_is_present(light_future);
	wait_for_future_if_it_is_present(batch_for_opaque.geometry_future);
	wait_for_future_if_it_is_present(batch_for_transparent.geometry_future);
	wait_for_future_if_it_is_present(batch_for_partially_transparent.geometry_future);
}

void						chunk_workspace::reset()
{
	auto 					reset_batch = [](batch &batch)
	{
		batch.blocks.clear();

		batch.geometry_future.reset();

		batch.vertices.clear();
		batch.texture_coordinates.clear();
		batch.light_levels.clear();
		batch.indices.clear();

		batch.model = nullptr;
	};

	landscape_future.reset();
	light_future.reset();

	reset_batch(batch_for_opaque);
	reset_batch(batch_for_transparent);
	reset_batch(batch_for_partially_transparent);
}