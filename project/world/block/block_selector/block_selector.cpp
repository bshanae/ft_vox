#include "block_selector.h"
#include "engine/model/model/model.h"
#include "world/block/block_selector/block_selector_renderer.h"

using namespace			engine;
using namespace			world;

static vector<float>	cube_vertices = {
	-0.5f, -0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
};

static vector<GLuint>	cube_indices = {
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

static vector<float>	left_vertices = {
	-0.5f, +0.5f, -0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, -0.5f
};

static vector<float>	right_vertices = {
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f
};

static vector<float>	front_vertices = {
	-0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f
};

static vector<float>	back_vertices = {
	-0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f
};

static vector<float>	top_vertices = {
	-0.5f, +0.5f, -0.5f,
	+0.5f, +0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, -0.5f
};

static vector<float>	bottom_vertices = {
	-0.5f, -0.5f, -0.5f,
	+0.5f, -0.5f, +0.5f,
	-0.5f, -0.5f, +0.5f,
	+0.5f, -0.5f, -0.5f
};

static vector<GLuint>	face_indices = {0, 1, 2, 3};

						block_selector::block_selector()
{
	layout = "Transparent";

	translation.prohibit_direct_access();
	translation.setter = [this](const vec3 &value)
	{
		translation.value = value;

		cube->translation = value;

		left->translation = value;
		right->translation = value;
		front->translation = value;
		back->translation = value;
		top->translation = value;
		bottom->translation = value;
	};
}

void 					block_selector::create_implementation()
{
	unique_object<block_selector>::create_implementation();

	cube = make_shared<::model>(model::lines);
	cube->bind(true);
	cube->add_vbo(3, cube_vertices);
	cube->add_ebo(cube_indices);
	cube->bind(false);

	left = make_shared<::model>(model::lines);
	left->bind(true);
	left->add_vbo(3, left_vertices);
	left->add_ebo(face_indices);
	left->bind(false);

	right = make_shared<::model>(model::lines);
	right->bind(true);
	right->add_vbo(3, right_vertices);
	right->add_ebo(face_indices);
	right->bind(false);

	front = make_shared<::model>(model::lines);
	front->bind(true);
	front->add_vbo(3, front_vertices);
	front->add_ebo(face_indices);
	front->bind(false);

	back = make_shared<::model>(model::lines);
	back->bind(true);
	back->add_vbo(3, back_vertices);
	back->add_ebo(face_indices);
	back->bind(false);

	top = make_shared<::model>(model::lines);
	top->bind(true);
	top->add_vbo(3, top_vertices);
	top->add_ebo(face_indices);
	top->bind(false);

	bottom = make_shared<::model>(model::lines);
	bottom->bind(true);
	bottom->add_vbo(3, bottom_vertices);
	bottom->add_ebo(face_indices);
	bottom->bind(false);
}

void					block_selector::render()
{
	block_selector_renderer::render(*this);
}