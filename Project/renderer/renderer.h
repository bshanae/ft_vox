#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/global.h"
#include "program/program.h"
#include "program/uniform.h"

class 							chunk;
class 							model;

class							renderer : public global<renderer>
{
public :
								renderer();
								~renderer() override = default;

	static void					render(const shared_ptr<model> &model);

private :

	inline static const path	path_to_vertex_shader = "Project/resources/shaders/vertex.glsl";
	inline static const path	path_to_fragment_shader = "Project/resources/shaders/fragment.glsl";

	unique_ptr<program>			program;

	uniform<mat4>				uniform_projection;
	uniform<mat4>				uniform_view;
	uniform<mat4>				uniform_transformation;
	uniform<vec3>				uniform_background;
	uniform<float>				uniform_fog_density;
	uniform<float>				uniform_fog_gradient;
};