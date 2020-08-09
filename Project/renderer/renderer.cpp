#include "renderer.h"

#include "map/chunk.h"
#include "camera/camera.h"

						renderer::renderer()
{
	program = make_unique<class program>(path_to_vertex_shader, path_to_fragment_shader);
	uniform_projection = program->create_uniform<mat4>("uniform_projection");
	uniform_view = program->create_uniform<mat4>("uniform_view");
	uniform_transformation = program->create_uniform<mat4>("uniform_transformation");
}

void					renderer::render(const shared_ptr<model> &model)
{
	auto 				instance = global<renderer>::instance();

	instance->program->bind(true);

#warning "Upload when changed"
	instance->uniform_projection.upload(camera::projection_matrix);
	instance->uniform_view.upload(camera::view_matrix);

	model->bind(true);
	instance->uniform_transformation.upload(model->transformation);
	glDrawElements(GL_TRIANGLES, model->number_of_indices, GL_UNSIGNED_INT, nullptr);
	model->bind(false);

	instance->program->bind(false);
}