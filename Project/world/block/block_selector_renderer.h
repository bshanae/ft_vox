#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "engine/object/unique_object.h"
#include "engine/program/program.h"
#include "engine/program/uniform.h"

class							model;
class							block_selector;

class							block_selector_renderer : public unique_object<block_selector_renderer>
{
public :
								block_selector_renderer();
								~block_selector_renderer() override = default;

	static void					render(const block_selector &selector);

private :

	inline static const path	path_to_vertex_shader = "Project/resources/shaders/selector.vertex.glsl";
	inline static const path	path_to_fragment_shader = "Project/resources/shaders/selector.fragment.glsl";

	unique_ptr<program>			program;

	uniform<mat4>				uniform_projection;
	uniform<mat4>				uniform_view;
	uniform<mat4>				uniform_transformation;

	float						epsilon;

	void						render(const shared_ptr<model> &model);
	void						render(const shared_ptr<model> &model, const vec3 &shift);
};


