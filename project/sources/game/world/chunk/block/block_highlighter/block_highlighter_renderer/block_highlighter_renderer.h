#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/main/rendering/program/program/program.h"
#include "engine/main/rendering/program/uniform/uniform.h"

#include "application/common/imports/opengl.h"
#include "application/common/imports/std.h"

namespace						engine
{
	class						model;
}

namespace						game
{

	class						block_highlighter;
	class 						block_highlighter_renderer;
}

class							game::block_highlighter_renderer :
									public engine::object,
									public engine::unique_object_constructor<block_highlighter_renderer>
{
public :
								block_highlighter_renderer();
								~block_highlighter_renderer() override = default;

	static void					render(const block_highlighter &selector);

private :

	inline static const path	path_to_vertex_shader = "Project/resources/shaders/selector.vertex.glsl";
	inline static const path	path_to_fragment_shader = "Project/resources/shaders/selector.fragment.glsl";

	unique_ptr<engine::program>	program;

	engine::uniform<mat4>		uniform_projection;
	engine::uniform<mat4>		uniform_view;
	engine::uniform<mat4>		uniform_transformation;

	float						epsilon;

	void						render(const shared_ptr<engine::model> &model);
	void						render(const shared_ptr<engine::model> &model, const vec3 &shift);
};


