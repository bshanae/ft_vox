#include "renderer.h"

#include "map/model.h"
#include "map/map_settings.h"
#include "camera/camera.h"

						renderer::renderer()
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
	uniform_fog_density.upload(1.f / (map_settings::visibility_limit * 0.95f));
	uniform_fog_gradient.upload(15.f);
	program->bind(false);
}

void					renderer::render(const shared_ptr<model> &model)
{
	auto 				instance = global<renderer>::instance();

	instance->program->bind(true);

	instance->uniform_projection.upload(camera::projection_matrix);
	instance->uniform_view.upload(camera::view_matrix);

	model->bind(true);
	instance->uniform_transformation.upload(model->transformation);
	glDrawElements(GL_TRIANGLES, model->number_of_indices, GL_UNSIGNED_INT, nullptr);
	model->bind(false);

	instance->program->bind(false);
}