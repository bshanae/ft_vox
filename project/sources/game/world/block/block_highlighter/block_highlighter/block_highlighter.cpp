#include "block_highlighter.h"

#include "engine/main/rendering/model/model/model.h"

#include "game/world/block/block_ptr/block_ptr.h"
#include "game/world/block/block_highlighter/block_highlighter_renderer/block_highlighter_renderer.h"

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

	translation = vec3(0);
	highlighted_face = block_face::left;
	should_render = false;
}

void					block_highlighter::highlight(const block_ptr &block, block_face face)
{
	const auto 			instance = get_instance();
	const auto 			translation = block.get_world_position() + vec3(0.5f);

	instance->translation = translation;

	instance->cube->set_translation(translation);
	instance->left->set_translation(translation);
	instance->right->set_translation(translation);
	instance->front->set_translation(translation);
	instance->back->set_translation(translation);
	instance->top->set_translation(translation);
	instance->bottom->set_translation(translation);

	instance->highlighted_face = face;

	instance->should_render = true;
}

void					block_highlighter::reset()
{
	get_instance()->should_render = false;
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
	if (should_render)
		block_highlighter_renderer::get_instance()->render(*this);
}