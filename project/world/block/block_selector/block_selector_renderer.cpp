#include "block_selector_renderer.h"

#include "engine/model/model/model.h"
#include "world/block/block_selector/block_selector.h"
#include "player/camera/camera.h"

using namespace			engine;
using namespace			world;
using namespace			player;

						block_selector_renderer::block_selector_renderer()
{
	layout = "System";

	program = make_unique<class program>(path_to_vertex_shader, path_to_fragment_shader);
	uniform_projection = program->create_uniform<mat4>("uniform_projection");
	uniform_view = program->create_uniform<mat4>("uniform_view");
	uniform_transformation = program->create_uniform<mat4>("uniform_transformation");
}

void					block_selector_renderer::render(const block_selector &selector)
{
	auto 				instance = unique_object<block_selector_renderer>::instance();

	float				distance;

	distance = glm::distance((vec3)camera::position, (vec3)selector.translation);
	instance->epsilon = (distance / 10.f) * 0.003f;

	instance->program->bind(true);

	instance->render(selector.cube);

	switch (selector.selected_face)
	{
		case (block::face::left) :
			instance->render(selector.left);
			break;

		case (block::face::right) :
			instance->render(selector.right);
			break;

		case (block::face::front) :
			instance->render(selector.front);
			break;

		case (block::face::back) :
			instance->render(selector.back);
			break;

		case (block::face::top) :
				instance->render(selector.top);
			break;

		case (block::face::bottom) :
			instance->render(selector.bottom);
			break;
	}

	instance->program->bind(false);
}

void					block_selector_renderer::render(const shared_ptr<model> &model)
{
	for (int x_indicator = -2; x_indicator <= +2; x_indicator++)
		for (int y_indicator = -2; y_indicator <= +2; y_indicator++)
			for (int z_indicator = -2; z_indicator <= +2; z_indicator++)
				render(
					model,
					vec3(
						(float)x_indicator * epsilon,
						(float)y_indicator * epsilon,
						(float)z_indicator * epsilon));
}

void					block_selector_renderer::render(const shared_ptr<model> &model, const vec3 &shift)
{
	const auto			original_translation = (vec3)model->translation;

	model->translation = (vec3)model->translation + shift;

	uniform_projection.upload(camera::projection_matrix);
	uniform_view.upload(camera::view_matrix);

	model->bind(true);

	uniform_transformation.upload(model->transformation);
	model->render();

	model->bind(false);

	model->translation = original_translation;
}