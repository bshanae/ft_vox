#pragma once

#include "common/opengl.h"
#include "common/aliases.h"
#include "common/array3.h"
#include "engine/object/usual_object/usual_object.h"
#include "world/block/block/block.h"
#include "world/block/block_id/block_id.h"
#include "world/chunk/chunk_settings.h"

namespace								engine
{
	class								model;
}

namespace								world
{
	class								block_id;
	class								world;
	class								chunk_renderer;

	class								chunk;
}

class									world::chunk :
											public chunk_settings::underlying_array,
											public enable_shared_from_this<chunk>
{
	friend class						::world::block_id;
	friend class 						::world::world;
	friend class 						::world::chunk_renderer;

public :

	using								index = array3<block, chunk_settings::size[0], chunk_settings::size[1], chunk_settings::size[2]>::index;

public :

	explicit							chunk(const vec3 &position);
										~chunk() override = default;

	property<read_only, vec3, chunk>	position;
	property<read_only, vec3, chunk>	center;

private :

	bool								can_be_regenerated = true;
	bool								is_visible = true;

// ------------------------------------ Workspaces

	struct								batch_workspace
	{
		function<bool(block &)>			predicate;

		vector<GLfloat>					vertices;
		vector<GLfloat>					texture_coordinates;
		vector<GLfloat>					light_levels;
		vector<GLuint>					indices;

		shared_ptr<engine::model>		model;

		future<void>					geometry_build_status;
	};

	enum class							batch_purpose
	{
		opaque,
		transparent,
		partially_transparent
	};

	batch_workspace						workspace_for_opaque;
	batch_workspace						workspace_for_transparent;
	batch_workspace						workspace_for_partially_transparent;

	future<void>						light_build_status;

// ------------------------------------ Build types

	enum class 							build_request
	{
		reset,
		light,
		geometry,
		model
	};

	enum class							build_phase
	{
		nothing_done,
		light_in_process,
		light_done,
		geometry_in_process,
		geometry_done,
		model_done
	}									build_phase = build_phase::nothing_done;

// ------------------------------------ Build functions

	void								build(build_request request);
	void								wait(build_request request);

	void								build_light();
	void								build_geometry(batch_workspace &workspace);
	void								build_model(batch_workspace &workspace);

// ------------------------------------ Build helpers

	float								calculate_ao(const index &index, axis axis, sign sign);
	static char							apply_ao(char light_level, float ao);

	void								build_block(batch_workspace &workspace, const index &index);
	void								build_quad(
											batch_workspace &workspace,
											const index &index,
											axis axis,
											sign sign,
											char light_level);
};