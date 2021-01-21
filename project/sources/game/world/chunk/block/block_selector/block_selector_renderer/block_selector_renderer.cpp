#include "block_selector_renderer.h"

#include "engine/rendering/main/model/model/model.h"
#include "engine/rendering/main/camera/camera.h"

#include "game/world/chunk/block/block_selector/block_selector/block_selector.h"

using namespace			engine;
using namespace			game;

						block_selector_renderer::block_selector_renderer()
{
	set_layout("System");

	program = make_unique<class program>(path_to_vertex_shader, path_to_fragment_shader);
	uniform_projection = program->create_uniform<mat4>("uniform_projection");
	uniform_view = program->create_uniform<mat4>("uniform_view");
	uniform_transformation = program->create_uniform<mat4>("uniform_transformation");
}

void					block_selector_renderer::render(const block_selector &selector)
{
	float				distance;

	distance = glm::distance(camera::get_instance()->get_position(), (vec3)selector.translation);
	epsilon = (distance / 10.f) * 0.003f;

	program->bind(true);

	render(selector.cube);

	switch (selector.selected_face)
	{
		case (block::left) :
			render(selector.left);
			break;

		case (block::right) :
			render(selector.right);
			break;

		case (block::front) :
			render(selector.front);
			break;

		case (block::back) :
			render(selector.back);
			break;

		case (block::top) :
				render(selector.top);
			break;

		case (block::bottom) :
			render(selector.bottom);
			break;
	}

	program->bind(false);
}

void					block_selector_renderer::render(const shared_ptr<model> &model)
{
	for (int x_indicator = -2; x_indicator <= +2; x_indicator++)
	for (int y_indicator = -2; y_indicator <= +2; y_indicator++)
	for (int z_indicator = -2; z_indicator <= +2; z_indicator++)
	{
		render
		(
			model,
			vec3((float)x_indicator, (float)y_indicator, (float)z_indicator) * epsilon
		);
	}
}

void					block_selector_renderer::render(const shared_ptr<model> &model, const vec3 &shift)
{
	const auto			original_translation = (vec3)model->get_translation();

	model->set_translation(model->get_translation() + shift);

	uniform_projection.upload(camera::get_instance()->get_projection_matrix());
	uniform_view.upload(camera::get_instance()->get_view_matrix());

	model->bind(true);

	uniform_transformation.upload(model->get_transformation());
	model->render();

	model->bind(false);

	model->set_translation(original_translation);
}