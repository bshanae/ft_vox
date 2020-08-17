#include "highlighter_renderer.h"
#include "world/chunk/model.h"
#include "world/chunk/highlighter.h"
#include "player/camera/camera.h"

						highlighter_renderer::highlighter_renderer()
{
	layout = "system";

	program = make_unique<class program>(path_to_vertex_shader, path_to_fragment_shader);
	uniform_projection = program->create_uniform<mat4>("uniform_projection");
	uniform_view = program->create_uniform<mat4>("uniform_view");
	uniform_transformation = program->create_uniform<mat4>("uniform_transformation");
}

void					highlighter_renderer::render(const highlighter &highlighter)
{
	constexpr float 	epsilon = 0.002f;

	auto 				instance = unique_object<highlighter_renderer>::instance();

	instance->program->bind(true);

	for (int x_indicator = -2; x_indicator <= +2; x_indicator++)
		for (int y_indicator = -2; y_indicator <= +2; y_indicator++)
			for (int z_indicator = -2; z_indicator <= +2; z_indicator++)
				instance->render_with_shift(
					highlighter.model,
					vec3(
						(float)x_indicator * epsilon,
						(float)y_indicator * epsilon,
						(float)z_indicator * epsilon));

	instance->program->bind(false);
}

void					highlighter_renderer::render_with_shift(const shared_ptr<model> &model, const vec3 &shift)
{
	const auto			original_translation = (vec3)model->translation;

	model->translation = (vec3)model->translation + shift;

	uniform_projection.upload(camera::projection_matrix);
	uniform_view.upload(camera::view_matrix);

	model->bind(true);

	uniform_transformation.upload(model->transformation);
	glDrawElements(GL_LINES, model->number_of_indices, GL_UNSIGNED_INT, nullptr);

	model->bind(false);

	model->translation = original_translation;
}