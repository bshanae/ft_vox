#pragma once

#include "engine/core/object/object/object.h"
#include "engine/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/rendering/main/program/program/program.h"
#include "engine/rendering/main/program/uniform/uniform.h"

#include "game/world/chunk/chunk/chunk/chunk.h"

#include "application/common/imports/glm.h"
#include "application/common/imports/opengl.h"
#include "application/common/imports/std.h"

namespace							engine
{
	class							model;
	class							program;
}

namespace							game
{
	class							chunk_renderer;
}

class								game::chunk_renderer :
										public engine::object,
										public engine::unique_object_constructor<game::chunk_renderer>
{
public :
									chunk_renderer();
									~chunk_renderer() override = default;

	void							set_apply_water_tint(bool value);

	void							render(const shared_ptr<chunk> &chunk, chunk::batch_purpose purpose);

private :

	inline static const path		path_to_vertex_shader = "project/resources/shaders/chunk.vertex.glsl";
	inline static const path		path_to_fragment_shader = "project/resources/shaders/chunk.fragment.glsl";

	bool							apply_water_tint;
	unique_ptr<engine::program>		program;

	engine::uniform<mat4>			uniform_projection;
	engine::uniform<mat4>			uniform_view;
	engine::uniform<mat4>			uniform_transformation;
	engine::uniform<int>			uniform_texture;
	engine::uniform<float>			uniform_alpha_discard_floor;
	engine::uniform<vec3>			uniform_background;
	engine::uniform<float>			uniform_fog_density;
	engine::uniform<float>			uniform_fog_gradient;
	engine::uniform<int>			uniform_apply_water_tint;
};