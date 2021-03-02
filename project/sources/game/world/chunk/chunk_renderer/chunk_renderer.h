#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/main/rendering/program/program/program.h"
#include "engine/main/rendering/program/uniform/uniform.h"

#include "game/world/chunk/chunk/chunk.h"

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

	enum class						group
	{
		opaque,
		transparent,
		partially_transparent
	};

									chunk_renderer();
									~chunk_renderer() override = default;

	static void						set_apply_water_tint(bool value);

	static void						render(const shared_ptr<chunk> &chunk, group group);

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

	static void						render
									(
										const shared_ptr<engine::model> &model,
										float alpha_discard_floor = 0.f
									);
};