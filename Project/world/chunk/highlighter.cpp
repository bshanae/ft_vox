#include "highlighter.h"
#include "world/chunk/model.h"
#include "world/chunk/highlighter_renderer.h"

static vector<float>	vertices = {
	-0.5f, -0.5f, -0.5f,
	-0.5f, +0.5f, -0.5f,
	+0.5f, +0.5f, -0.5f,
	+0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, +0.5f,
	-0.5f, +0.5f, +0.5f,
	+0.5f, +0.5f, +0.5f,
	+0.5f, -0.5f, +0.5f,
};

static vector<GLuint>	indices = {
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

						highlighter::highlighter()
{
	layout = "water";
}

void 					highlighter::create_implementation()
{
	unique_object<highlighter>::create_implementation();

	model = make_shared<::model>();
	model->bind(true);
	model->add_vbo(3, vertices);
	model->add_ebo(indices);
	model->bind(false);

}

void					highlighter::render()
{
	highlighter_renderer::render(*this);
}