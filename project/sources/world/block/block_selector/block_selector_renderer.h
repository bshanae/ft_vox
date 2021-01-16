#pragma once

#include "common/imports/opengl.h"
#include "common/imports/std.h"
#include "engine/object/unique_object/unique_object.h"
#include "engine/program/program/program.h"
#include "engine/program/uniform/uniform.h"

namespace						engine
{
	class						model;
}

namespace						world
{

	class						block_selector;

	class 						block_selector_renderer;
}

class							world::block_selector_renderer : public engine::unique_object<block_selector_renderer>
{
public :
								block_selector_renderer();
								~block_selector_renderer() override = default;

	void						render(const block_selector &selector);

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


