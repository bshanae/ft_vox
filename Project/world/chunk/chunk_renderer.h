#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/global.h"
#include "world/program/program.h"
#include "world/program/uniform.h"

class 							chunk;
class 							model;

class							chunk_renderer : public global<chunk_renderer>
{
public :
								chunk_renderer();
								~chunk_renderer() override = default;

	enum class					mod
	{
		main,
		water
	};

	static void					render(const shared_ptr<chunk> &chunk, mod mod);

private :

	inline static const path	path_to_vertex_shader = "Project/resources/shaders/chunk.vertex.glsl";
	inline static const path	path_to_fragment_shader = "Project/resources/shaders/chunk.fragment.glsl";

	unique_ptr<program>			program;

	uniform<mat4>				uniform_projection;
	uniform<mat4>				uniform_view;
	uniform<mat4>				uniform_transformation;
	uniform<vec3>				uniform_background;
	uniform<float>				uniform_fog_density;
	uniform<float>				uniform_fog_gradient;
};