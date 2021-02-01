#include "block_highlighter.h"

#include "engine/main/rendering/model/model/model.h"

#include "game/world/chunk/block/block_highlighter/block_highlighter_renderer/block_highlighter_renderer.h"

using namespace			engine;
using namespace			game;

static vector<float>	cube_vertices =
{
	-0.5f, -0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
};

static vector<GLuint>	cube_indices =
{
	0, 1,
	1, 2,
	2, 3,
	3, 0,

	4, 5,
	5, 6,
	6, 7,
	7, 4,

	0, 4,
	1, 5,
	2, 6,
	3, 7
};

static vector<float>	left_vertices =
{
	-0.5f, +0.5f, -0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, -0.5f
};

static vector<float>	right_vertices =
{
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f
};

static vector<float>	front_vertices =
{
	-0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f
};

static vector<float>	back_vertices =
{
	-0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f
};

static vector<float>	top_vertices =
{
	-0.5f, +0.5f, -0.5f,
	+0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, -0.5f
};

static vector<float>	bottom_vertices =
{
	-0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f
};

static vector<GLuint>	face_indices = {0, 1, 2, 3};

						block_highlighter::block_highlighter()
{
	set_layout("Opaque");
}

vec3					block_highlighter::get_translation()
{
	return get_instance()->translation;
}

block_face				block_highlighter::get_selected_face()
{
	return get_instance()->selected_face;
}

void					block_highlighter::set_translation(const vec3 &value)
{
	const auto			instance = get_instance();

	instance->translation = value;

	instance->cube->set_translation(value);
	instance->left->set_translation(value);
	instance->right->set_translation(value);
	instance->front->set_translation(value);
	instance->back->set_translation(value);
	instance->top->set_translation(value);
	instance->bottom->set_translation(value);
}

void					block_highlighter::set_selected_face(block_face face)
{
	get_instance()->selected_face = face;
}

void 					block_highlighter::when_initialized()
{
	cube = make_shared<::model>(model::lines);
	cube->use(true);
	cube->add_vbo(3, cube_vertices);
	cube->add_ebo(cube_indices);
	cube->use(false);

	left = make_shared<::model>(model::lines);
	left->use(true);
	left->add_vbo(3, left_vertices);
	left->add_ebo(face_indices);
	left->use(false);

	right = make_shared<::model>(model::lines);
	right->use(true);
	right->add_vbo(3, right_vertices);
	right->add_ebo(face_indices);
	right->use(false);

	front = make_shared<::model>(model::lines);
	front->use(true);
	front->add_vbo(3, front_vertices);
	front->add_ebo(face_indices);
	front->use(false);

	back = make_shared<::model>(model::lines);
	back->use(true);
	back->add_vbo(3, back_vertices);
	back->add_ebo(face_indices);
	back->use(false);

	top = make_shared<::model>(model::lines);
	top->use(true);
	top->add_vbo(3, top_vertices);
	top->add_ebo(face_indices);
	top->use(false);

	bottom = make_shared<::model>(model::lines);
	bottom->use(true);
	bottom->add_vbo(3, bottom_vertices);
	bottom->add_ebo(face_indices);
	bottom->use(false);
}

void					block_highlighter::when_rendered()
{
	block_highlighter_renderer::get_instance()->render(*this);
}