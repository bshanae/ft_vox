#include "block_highlighter_renderer.h"

#include "engine/main/rendering/model/model/model.h"
#include "engine/main/rendering/camera/camera/camera.h"

#include "game/world/chunk/block/block_face/block_face.h"
#include "game/world/chunk/block/block_highlighter/block_highlighter/block_highlighter.h"

using namespace			engine;
using namespace			game;

						block_highlighter_renderer::block_highlighter_renderer()
{
	set_layout("System");

	program = make_unique<class program>(path_to_vertex_shader, path_to_fragment_shader);
	uniform_projection = program->create_uniform<mat4>("uniform_projection");
	uniform_view = program->create_uniform<mat4>("uniform_view");
	uniform_transformation = program->create_uniform<mat4>("uniform_transformation");
}

void					block_highlighter_renderer::render(const block_highlighter &selector)
{
	const auto 			instance = get_instance();

	float				distance;

	distance = glm::distance(camera::get_position(), (vec3)selector.translation);
	instance->epsilon = (distance / 10.f) * 0.003f;

	instance->program->use(true);

	instance->render(selector.cube);

	switch (selector.selected_face)
	{
		case (block_face::left) :
			instance->render(selector.left);
			break;

		case (block_face::right) :
			instance->render(selector.right);
			break;

		case (block_face::front) :
			instance->render(selector.front);
			break;

		case (block_face::back) :
			instance->render(selector.back);
			break;

		case (block_face::top) :
			instance->render(selector.top);
			break;

		case (block_face::bottom) :
			instance->render(selector.bottom);
			break;
	}

	instance->program->use(false);
}

void					block_highlighter_renderer::render(const shared_ptr<model> &model)
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

void					block_highlighter_renderer::render(const shared_ptr<model> &model, const vec3 &shift)
{
	const auto			original_translation = (vec3)model->get_translation();

	model->set_translation(model->get_translation() + shift);

	uniform_projection.upload(camera::get_projection_matrix());
	uniform_view.upload(camera::get_view_matrix());

	model->use(true);

	uniform_transformation.upload(model->get_transformation());
	model->render();

	model->use(false);

	model->set_translation(original_translation);
}