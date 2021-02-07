#pragma once

#include "application/common/templates/singleton/singleton.h"

#include "game/world/chunk/chunk/building/chunk_workspace/chunk_workspace.h"

namespace						game
{
	class						chunk_build_director;
}

class							game::chunk_build_director : public singleton<game::chunk_build_director>
{
	using						data_type = unordered_map<shared_ptr<chunk>, shared_ptr<chunk_workspace>>;

public :
								chunk_build_director() = default;
								~chunk_build_director() override = default;

	struct 						build
	{
		using					model_type = shared_ptr<engine::model>;

		model_type				model_for_opaque;
		model_type				model_for_transparent;
		model_type				model_for_partially_transparent;
	};

	static optional<build>		process_build(const shared_ptr<chunk> &chunk);
	static void 				invalidate_build(const shared_ptr<chunk> &chunk);

private :

	 data_type					data;

	shared_ptr<chunk_workspace>	get_workspace(const shared_ptr<chunk> &chunk) const;
	shared_ptr<chunk_workspace>	get_or_create_workspace(const shared_ptr<chunk> &chunk);

	static build				package_build(const shared_ptr<chunk_workspace> &workspace);

	static bool					is_chunk_present_and_has_light(const vec3 &position);
	static bool					are_all_neighbors_present_and_have_light(const shared_ptr<chunk> &chunk);

	static void					log_requesting_light_build(const shared_ptr<chunk> &chunk);
	static void					log_requesting_geometry_build(const shared_ptr<chunk> &chunk);
	static void					log_requesting_model_build(const shared_ptr<chunk> &chunk);
};


