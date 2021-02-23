#pragma once

#include "application/common/imports/std.h"

#include "game/world/chunk/block/block_pointer/block_pointer.h"
#include "game/world/chunk/chunk/chunk/chunk_settings.h"

namespace							engine
{
	class							model;
}

namespace							game
{
	class 							block;
	class 							chunk;
	class 							chunk_workspace;
}

class 								game::chunk_workspace
{
public :

	struct							batch
	{
		vector<block_pointer>		blocks;

		optional<future<void>>		geometry_future;

		vector<float>				vertices;
		vector<float>				texture_coordinates;
		vector<float>				light_levels;
		vector<uint>				indices;

		shared_ptr<engine::model>	model;
	};

	enum							state
	{
		nothing_done,
		landscape_in_process,
		landscape_done,
		light_in_process,
		light_done,
		geometry_in_process,
		geometry_done,
		model_in_process,
		model_done
	};

	explicit						chunk_workspace(const shared_ptr<chunk> &chunk);

	void 							wait();
	void							reset();

	const shared_ptr<chunk>			chunk;
	atomic<state>					state;

	optional<future<void>>			landscape_future;
	optional<future<void>>			light_build_future;

	batch							batch_for_opaque;
	batch							batch_for_transparent;
 	batch							batch_for_partially_transparent;

 	// TODO Maybe redo this logic
 	bool							build_at_once;
};