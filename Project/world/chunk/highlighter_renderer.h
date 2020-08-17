#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "application/unique_object.h"
#include "world/program/program.h"
#include "world/program/uniform.h"

class							model;
class							highlighter;

class							highlighter_renderer : public unique_object<highlighter_renderer>
{
public :
								highlighter_renderer();
								~highlighter_renderer() override = default;

	static void					render(const highlighter &highlighter);

private :

	inline static const path	path_to_vertex_shader = "Project/resources/shaders/highlighter.vertex.glsl";
	inline static const path	path_to_fragment_shader = "Project/resources/shaders/highlighter.fragment.glsl";

	unique_ptr<program>			program;

	uniform<mat4>				uniform_projection;
	uniform<mat4>				uniform_view;
	uniform<mat4>				uniform_transformation;

	void						render_with_shift(const shared_ptr<model> &model, const vec3 &shift);
};


