#include "chunk_renderer.h"

#include "world/chunk/model.h"
#include "world/chunk/chunk.h"
#include "world/world/world_settings.h"
#warning "Receive matrices directly from player"
#include "player/camera/camera.h"

						chunk_renderer::chunk_renderer()
{
	program = make_unique<class program>(path_to_vertex_shader, path_to_fragment_shader);
	uniform_projection = program->create_uniform<mat4>("uniform_projection");
	uniform_view = program->create_uniform<mat4>("uniform_view");
	uniform_transformation = program->create_uniform<mat4>("uniform_transformation");
	uniform_background = program->create_uniform<vec3>("uniform_background");
	uniform_fog_density = program->create_uniform<float>("uniform_fog_density");
	uniform_fog_gradient = program->create_uniform<float>("uniform_fog_gradient");

	program->bind(true);
	uniform_background.upload(application_settings::background);
	uniform_fog_gradient.upload(15.f);
	program->bind(false);
}

void					chunk_renderer::render(const shared_ptr<chunk> &chunk, mod mod)
{
	auto 				instance = global<chunk_renderer>::instance();
	shared_ptr<model>	model;

	if (not chunk->is_visible)
		return ;

	switch (mod)
	{
		case (mod::main) :
			model = chunk->main_workspace.model;
			break ;

		case (mod::water) :
			model = chunk->water_workspace.model;
			break ;
	}

	if (not model)
		return ;

	instance->program->bind(true);

	instance->uniform_projection.upload(camera::projection_matrix);
	instance->uniform_view.upload(camera::view_matrix);
	instance->uniform_fog_density.upload(1.f / (world_settings::visibility_limit * 0.95f));

	model->bind(true);
	instance->uniform_transformation.upload(model->transformation);
	glDrawElements(GL_TRIANGLES, model->number_of_indices, GL_UNSIGNED_INT, nullptr);
	model->bind(false);

	instance->program->bind(false);
}