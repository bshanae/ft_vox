#pragma once

#include "application/common/imports/std.h"

#include "game/world/block/block_ptr/block_ptr.h"
#include "game/world/chunk/chunk/chunk_settings.h"
#include "game/world/chunk/generation/chunk_generation_task/chunk_generation_task/chunk_generation_task.h"
#include "game/world/chunk/generation/utilities/biome/biomes/abstract/abstract.h"

namespace								engine
{
	class								model;
}

namespace								game
{
	class 								block;
	class 								chunk;
	class 								chunk_workspace;
}

class 									game::chunk_workspace final
{
public :

	struct								batch
	{
		vector<block_ptr>				blocks;

		optional<future<void>>			geometry_future;

		vector<float>					vertices;
		vector<float>					texture_coordinates;
		vector<float>					light_levels;
		vector<uint>					indices;

		shared_ptr<engine::model>		model;
	};

	struct								column_info
	{
		shared_ptr<biomes::abstract>	biome;
		int								final_height;
		bool							is_height_affected_by_cave;
	};

public :

	explicit							chunk_workspace(const shared_ptr<chunk> &chunk);
										~chunk_workspace();

	void								reset();

	const shared_ptr<chunk>				chunk;

	using								column_info_array = array3<column_info, chunk_settings::size[0], 1, chunk_settings::size[2]>;
	column_info_array					column_infos;

	optional<future<void>>				landscape_future;
	optional<future<void>>				light_future;

	batch								batch_for_opaque;
	batch								batch_for_transparent;
 	batch								batch_for_partially_transparent;
};