#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/main/rendering/texture/cubemap/cubemap.h"
#include "engine/main/rendering/program/program/program.h"

#include "application/common/imports/std.h"

namespace						engine
{
	class						model;
	class						cubemap;
}

namespace						game
{
	class						skybox;
}

class							game::skybox :
									public engine::object,
									public engine::unique_object_constructor<skybox>
{
public :
								skybox();
								~skybox() override = default;
private :

	inline static const path	path_to_vertex_shader = "project/resources/shaders/skybox.vertex.glsl";
	inline static const path	path_to_fragment_shader = "project/resources/shaders/skybox.fragment.glsl";

	bool						is_enabled;

	shared_ptr<engine::model>	model;
	shared_ptr<engine::cubemap>	cubemap;

	unique_ptr<engine::program>	program;
	engine::uniform<mat4>		uniform_projection;
	engine::uniform<mat4>		uniform_view;
	engine::uniform<int>		uniform_cubemap;

	void						when_updated() override;
	void						when_rendered() override;

	void						build_model();
	void						build_cubemap();
	void						build_program();
	void						initialize_program();
};