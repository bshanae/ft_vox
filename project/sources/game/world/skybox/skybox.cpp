#include "skybox.h"

#include "engine/main/rendering/camera/camera/camera.h"
#include "engine/main/rendering/model/model/model.h"
#include "engine/main/rendering/texture/cubemap/cubemap.h"
#include "engine/main/rendering/texture/cubemap_loader/cubemap_loader.h"

#include "game/world/skybox/skybox_settings.h"

using namespace			game;

						skybox::skybox()
{
	set_layout("Background");

	build_model();
	build_cubemap();
	build_program();
	initialize_program();
}

void					skybox::when_rendered()
{
	mat4 				view_matrix;

	program->use(true);
	model->use(true);
	cubemap->use(true);

	view_matrix = mat4(mat3(engine::camera::get_view_matrix()));

	uniform_projection.upload(engine::camera::get_projection_matrix());
	uniform_view.upload(view_matrix);

	model->render();

	cubemap->use(false);
	model->use(false);
	program->use(false);

	program->use(true);
}

void					skybox::build_model()
{
	static const
	vector<float>		vertices =
	{
		-1.0, -1.0, +1.0,
		+1.0, -1.0, +1.0,
		+1.0, +1.0, +1.0,
		-1.0, +1.0, +1.0,

		-1.0, -1.0, -1.0,
		+1.0, -1.0, -1.0,
		+1.0, +1.0, -1.0,
		-1.0, +1.0, -1.0
	};

	static const
	vector<GLuint>		indices =
	{
		0, 1, 2,
		2, 3, 0,
		1, 5, 6,
		6, 2, 1,
		7, 6, 5,
		5, 4, 7,
		4, 0, 3,
		3, 7, 4,
		4, 5, 1,
		1, 0, 4,
		3, 2, 6,
		6, 7, 3
	};

	model = make_shared<engine::model>();

	model->use(true);
	model->add_vbo(3, vertices);
	model->add_ebo(indices);
	model->use(false);
}

void					skybox::build_cubemap()
{
	cubemap = engine::cubemap_loader::load
	(
		skybox_settings::source_right,
		skybox_settings::source_left,
		skybox_settings::source_top,
		skybox_settings::source_bottom,
		skybox_settings::source_front,
		skybox_settings::source_back
	);
}

void					skybox::build_program()
{
	program = make_unique<engine::program>(path_to_vertex_shader, path_to_fragment_shader);
	uniform_projection = program->create_uniform<mat4>("uniform_projection");
	uniform_view = program->create_uniform<mat4>("uniform_view");
	uniform_cubemap = program->create_uniform<int>("uniform_cubemap");
}

void					skybox::initialize_program()
{
	program->use(true);
	uniform_cubemap.upload(0);
	program->use(true);
}