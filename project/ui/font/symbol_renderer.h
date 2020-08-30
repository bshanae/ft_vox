#pragma once

#include "engine/object/unique_object.h"
#include "engine/program/program.h"

class							model;
class							symbol;

class							symbol_renderer : public unique_object<symbol_renderer>
{
public :
								symbol_renderer();
								~symbol_renderer() override = default;

	static void					render(const symbol &symbol, const ivec2 &position);

private :

	shared_ptr<model>			model;

	inline static const path	path_to_vertex_shader = "project/resources/shaders/symbol.vertex.glsl";
	inline static const path	path_to_fragment_shader = "project/resources/shaders/symbol.fragment.glsl";

	unique_ptr<program>			program;

	uniform<mat4>				uniform_projection;
	uniform<mat4>				uniform_transformation;
	uniform<int>				uniform_texture;
};


