#include "chunk_renderer.h"

#include "engine/core/core_settings.h"
#include "engine/model/model/model.h"
#include "world/texture_atlas/texture_atlas.h"
#include "world/chunk/chunk.h"
#include "world/world/world_settings.h"
#include "player/camera/camera.h"

using namespace			engine;
using namespace			world;
using namespace			player;

						chunk_renderer::chunk_renderer()
{
	layout = "System";
	should_be_updated = false;
	should_be_rendered = false;

	apply_water_tint = false;

	program = make_unique<class program>(path_to_vertex_shader, path_to_fragment_shader);
	uniform_projection = program->create_uniform<mat4>("uniform_projection");
	uniform_view = program->create_uniform<mat4>("uniform_view");
	uniform_transformation = program->create_uniform<mat4>("uniform_transformation");
	uniform_texture = program->create_uniform<int>("uniform_texture");
	uniform_alpha_discard_floor = program->create_uniform<float>("uniform_alpha_discard_floor");
	uniform_background = program->create_uniform<vec3>("uniform_background");
	uniform_fog_density = program->create_uniform<float>("uniform_fog_density");
	uniform_fog_gradient = program->create_uniform<float>("uniform_fog_gradient");
	uniform_apply_water_tint = program->create_uniform<int>("uniform_apply_water_tint");

	program->bind(true);
	uniform_background.upload(core_settings::background);
	uniform_texture.upload(0);
	uniform_fog_density.upload(1.f / (world_settings::visibility_limit - chunk_settings::size[0] * 1.5f));
	uniform_fog_gradient.upload(15.f);
	uniform_apply_water_tint.upload(0);
	program->bind(false);
}

void					chunk_renderer::render(const shared_ptr<chunk> &chunk, chunk::batch_purpose purpose)
{
	auto 				instance = unique_object<chunk_renderer>::instance();

	shared_ptr<model>	model;
	float				alpha_discard_floor = 0.f;

	if (not chunk->is_visible)
		return ;

	switch (purpose)
	{
		case (chunk::batch_purpose::opaque) :
			model = chunk->workspace_for_opaque.model;
			break ;

		case (chunk::batch_purpose::transparent) :
			model = chunk->workspace_for_transparent.model;
			break ;

		case (chunk::batch_purpose::partially_transparent) :
			model = chunk->workspace_for_partially_transparent.model;
			alpha_discard_floor = 0.8f;
			break ;
	}

	if (not model)
		return ;

	instance->program->bind(true);

	instance->uniform_projection.upload(camera::projection_matrix);
	instance->uniform_view.upload(camera::view_matrix);
	instance->uniform_alpha_discard_floor.upload(alpha_discard_floor);
	instance->uniform_apply_water_tint.upload(apply_water_tint.value);

	model->bind(true);
	texture_atlas::instance()->bind(true);

	instance->uniform_transformation.upload(model->transformation);
	model->render();

	texture_atlas::instance()->bind(false);
	model->bind(false);
	instance->program->bind(false);
}