#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/array3.h"
#include "application/object_template.h"
#include "map/model.h"

#include "map/block.h"

struct									chunk_settings
{
	static
	constexpr int						size[3] = {4, 4, 4};

	static inline
	const vec3							size_as_vector = vec3(size[0], size[1], size[2]);
};

class									chunk :
											public object_template<chunk>,
											private array3<block, chunk_settings::size[0], chunk_settings::size[1], chunk_settings::size[2]>
{
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

	using 								neighbor_provider_type = function<shared_ptr<chunk>(const shared_ptr<chunk> &, axis, sign)>;
	static
	inline
	neighbor_provider_type				neighbor_provider = nullptr;

	void								render() override;

	void								build();

	void								build_model();
	void								build_block(const index &index);
	void								build_quad(axis axis, sign sign, const index &index, int light_level);

	void 								calculate_lighting();
};