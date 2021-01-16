#include "symbol_renderer.h"

#include "engine/window/window.h"
#include "engine/model/model/model.h"
#include "ui/font/symbol/symbol.h"

using namespace		engine;
using namespace		ui;

					symbol_renderer::symbol_renderer()
{
	unique_object::layout = "System";
	unique_object::should_be_rendered = false;
	unique_object::should_be_updated = false;

	program = make_unique<class program>(path_to_vertex_shader, path_to_fragment_shader);
	uniform_projection = program->create_uniform<mat4>("uniform_projection");
	uniform_transformation = program->create_uniform<mat4>("uniform_transformation");
	uniform_texture = program->create_uniform<int>("uniform_texture");

	program->bind(true);
	uniform_projection.upload(ortho(0.f, (float)window::size.x, (float)window::size.y, 0.f));
	uniform_texture.upload(0);
	program->bind(false);

	vector<GLfloat>	vertices =
	{
		1.f, 1.f, 0.0f,
		1.f, 0.f, 0.0f,
		0.f, 0.f, 0.0f,
		0.f, 1.f, 0.0f
	};

	vector<GLfloat>	texture_coordinates =
	{
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};

	vector<GLuint>	indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	model = make_shared<::model>();

	model->bind(true);

	model->add_vbo(3, vertices);
	model->add_vbo(2, texture_coordinates);
	model->add_ebo(indices);

	model->bind(false);
}

void				symbol_renderer::render(const symbol &symbol, const ivec2 &position)
{
	auto			instance = unique_object::get_instance();

	instance->model->set_translation(vec3(position.x, position.y, 0));
	instance->model->set_scaling(vec3(symbol.get_size().x, symbol.get_size().y, 0));

	instance->program->bind(true);
	instance->model->bind(true);
	symbol.bind(true);

	instance->uniform_transformation.upload(instance->model->get_transformation());
	instance->model->render();

	symbol.bind(false);
	instance->model->bind(false);
	instance->program->bind(false);
}