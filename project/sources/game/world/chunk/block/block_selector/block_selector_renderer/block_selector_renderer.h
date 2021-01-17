#pragma once

#include "engine/core/object/unique_object/unique_object.h"
#include "engine/rendering/main/program/program/program.h"
#include "engine/rendering/main/program/uniform/uniform.h"

#include "application/common/imports/opengl.h"
#include "application/common/imports/std.h"

namespace						engine
{
	class						model;
}

namespace						game
{

	class						block_selector;

	class 						block_selector_renderer;
}

class							game::block_selector_renderer : public engine::unique_object<block_selector_renderer>
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


