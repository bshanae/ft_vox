#pragma once

#include "application/common/imports/std.h"

#include "game/world/block/block_ptr/block_ptr.h"
#include "game/world/chunk/chunk/chunk_settings.h"
#include "game/world/chunk/chunk_generation_task/chunk_generation_task/chunk_generation_task.h"

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

class 								game::chunk_workspace final
{
public :

	struct							batch
	{
		vector<block_ptr>			blocks;

		optional<future<void>>		geometry_future;

		vector<float>				vertices;
		vector<float>				texture_coordinates;
		vector<float>				light_levels;
		vector<uint>				indices;

		shared_ptr<engine::model>	model;
	};

public :

	explicit						chunk_workspace(const shared_ptr<chunk> &chunk);
									~chunk_workspace();

	void							reset();

	const shared_ptr<chunk>			chunk;

	optional<future<void>>			landscape_future;
	optional<future<void>>			light_future;

	batch							batch_for_opaque;
	batch							batch_for_transparent;
 	batch							batch_for_partially_transparent;
};