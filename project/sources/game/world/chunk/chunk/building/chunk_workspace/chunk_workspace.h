#pragma once

#include "application/common/imports/std.h"

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
		function<bool(block &)>		filter;

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
		light_in_process,
		light_done,
		geometry_in_process,
		geometry_done,
		model_in_process,
		model_done
	};

	explicit						chunk_workspace(const shared_ptr<chunk> &chunk);
	void							reset();

	const shared_ptr<chunk>			chunk;
	atomic<state>					state;

	using							light_levels_type = array3<char, chunk_settings::size[0], chunk_settings::size[1], chunk_settings::size[2]>;
	light_levels_type				light_levels;
	optional<future<void>>			light_build_future;

	batch							batch_for_opaque;
	batch							batch_for_transparent;
 	batch							batch_for_partially_transparent;
};