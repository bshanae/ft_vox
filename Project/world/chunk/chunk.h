#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/array3.h"
#include "application/object_template.h"
#include "world/block/block.h"
#include "world/block/block_id.h"
#include "world/chunk/model.h"
#include "world/chunk/chunk_settings.h"

class										chunk :
												public chunk_settings::underlying_array,
												public enable_shared_from_this<chunk>
{
	friend class							block_id;
	friend class 							world;
	friend class 							chunk_renderer;

public :

	using									index = array3<block, chunk_settings::size[0], chunk_settings::size[1], chunk_settings::size[2]>::index;

public :

	explicit								chunk(const vec3 &position);
											~chunk() override = default;

	property<read_only, vec3, chunk>		position;
	property<read_only, vec3, chunk>		center;

private :

	struct									model_workspace
	{
		function<bool(enum block::type)>	predicate;

		vector<GLfloat>						vertices;
		vector<GLfloat>						texture_coordinates;
		vector<GLfloat>						light_levels;
		vector<GLuint>						indices;

		shared_ptr<::model>					model;
	};

	model_workspace							main_workspace;
	model_workspace							water_workspace;

	bool									is_visible = true;

	enum class 								build_request
	{
		reset,
		light,
		model
	};

	enum class								build_phase
	{
		nothing_done,
		light_done,
		model_done
	}										build_phase = build_phase::nothing_done;

	void									build(build_request request);

// ---------------------------------------- Light

	void									calculate_light();
	float									calculate_ao(const index &index, axis axis, sign sign);
	static char								apply_ao(char light_level, float ao);

// ---------------------------------------- Model

	void									build_model(model_workspace &workspace);
	void									build_block(model_workspace &workspace, const index &index);
	void									build_quad(
												model_workspace &workspace,
												const index &index,
												axis axis,
												sign sign,
												char light_level);
};