#include "symbol_renderer.h"

#include "engine/main/rendering/model/model/model.h"
#include "engine/extensions/ui/font/symbol/symbol.h"
#include "engine/main/system/window/window/window.h"

using namespace		engine;
using namespace		engine::ui;

					symbol_renderer::symbol_renderer()
{
	set_layout("System");

	program = make_unique<class program>(path_to_vertex_shader, path_to_fragment_shader);
	uniform_projection = program->create_uniform<mat4>("uniform_projection");
	uniform_transformation = program->create_uniform<mat4>("uniform_transformation");
	uniform_texture = program->create_uniform<int>("uniform_texture");

	program->use(true);
	uniform_projection.upload(ortho(0.f, (float)window::get_size().x, (float)window::get_size().y, 0.f));
	uniform_texture.upload(0);
	program->use(false);

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

	model->use(true);

	model->add_vbo(3, vertices);
	model->add_vbo(2, texture_coordinates);
	model->add_ebo(indices);

	model->use(false);
}

void				symbol_renderer::render(symbol &symbol, const ivec2 &position)
{
	auto			instance = get_instance();

	instance->model->set_translation(vec3(position.x, position.y, 0));
	instance->model->set_scaling(vec3(symbol.get_size().x, symbol.get_size().y, 0));

	instance->program->use(true);
	instance->model->use(true);
	symbol.use(true);

	instance->uniform_transformation.upload(instance->model->get_transformation());
	instance->model->render();

	symbol.use(false);
	instance->model->use(false);
	instance->program->use(false);
}