#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "core/object/unique_object.h"
#include "world/program/program.h"
#include "world/program/uniform.h"
#include "world/chunk/chunk.h"

class 							model;

class							chunk_renderer : public unique_object<chunk_renderer>
{
public :
								chunk_renderer();
								~chunk_renderer() override = default;

	static void					render(const shared_ptr<chunk> &chunk, chunk::batch_purpose purpose);

private :

	inline static const path	path_to_vertex_shader = "Project/resources/shaders/chunk.vertex.glsl";
	inline static const path	path_to_fragment_shader = "Project/resources/shaders/chunk.fragment.glsl";

	unique_ptr<program>			program;

	uniform<mat4>				uniform_projection;
	uniform<mat4>				uniform_view;
	uniform<mat4>				uniform_transformation;
	uniform<float>				uniform_alpha_discard_floor;
	uniform<vec3>				uniform_background;
	uniform<float>				uniform_fog_density;
	uniform<float>				uniform_fog_gradient;
};