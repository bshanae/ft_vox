#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/array3.h"
#include "application/object_template.h"
#include "map/model.h"
#include "map/block.h"
#include "map/block_id.h"
#include "map/chunk_settings.h"

class									chunk :
											public object_template<chunk>,
											public chunk_settings::underlying_array
{
	friend class						block_id;
	friend class						chunk_editor;
	friend class 						map;
	friend class 						renderer;

public :

	using								index = array3<block, chunk_settings::size[0], chunk_settings::size[1], chunk_settings::size[2]>::index;

public :

	explicit							chunk(const vec3 &position);
										~chunk() override = default;

	property<read_only, vec3, chunk>	position;
	property<read_only, vec3, chunk>	center;

private :

	shared_ptr<model>					model;

	vector<GLfloat>						vertices;
	vector<GLfloat>						texture_coordinates;
	vector<GLfloat>						light_levels;
	vector<GLuint>						indices;

	void								render() override;

	enum class 							build_request
	{
		reset,
		light,
		model
	};

	enum class							build_phase
	{
		nothing_done,
		light_done,
		model_done
	}									build_phase = build_phase::nothing_done;

	void								build(build_request request);

	void								calculate_light();
	float								calculate_ao(const index &index, axis axis, sign sign);
	static char							apply_ao(char light_level, float ao);

	void								build_model();
	void								build_block(const index &index);
	void								build_quad(const index &index, axis axis, sign sign, char light_level);
};