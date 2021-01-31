#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/main/rendering/program/program/program.h"

namespace						engine
{
	class 						model;

	namespace					ui
	{
		class					symbol;
		class					symbol_renderer;
	}
}

class							engine::ui::symbol_renderer :
									public engine::object,
									public engine::unique_object_constructor<symbol_renderer>
{
public :
								symbol_renderer();
								~symbol_renderer() override = default;

								// TODO override?
	static void					render(symbol &symbol, const ivec2 &position);

private :

	shared_ptr<engine::model>	model;

	inline static const path	path_to_vertex_shader = "project/resources/shaders/symbol.vertex.glsl";
	inline static const path	path_to_fragment_shader = "project/resources/shaders/symbol.fragment.glsl";

	unique_ptr<engine::program>	program;

	engine::uniform<mat4>		uniform_projection;
	engine::uniform<mat4>		uniform_transformation;
	engine::uniform<int>		uniform_texture;
};

