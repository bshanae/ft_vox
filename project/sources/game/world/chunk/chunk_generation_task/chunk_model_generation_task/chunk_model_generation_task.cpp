#include "chunk_model_generation_task.h"

#include "engine/main/rendering/model/model/model.h"

#include "game/world/chunk/chunk_workspace/chunk_workspace.h"

using namespace		game;

					chunk_model_generation_task::chunk_model_generation_task() : chunk_generation_task(false)
{}

void 				chunk_model_generation_task::do_launch(chunk_workspace &workspace)
{
	process_batch(workspace, workspace.batch_for_opaque);
	process_batch(workspace, workspace.batch_for_transparent);
	process_batch(workspace, workspace.batch_for_partially_transparent);
}

void				chunk_model_generation_task::process_batch(chunk_workspace &workspace, chunk_workspace::batch &batch)
{
	batch.model = make_shared<engine::model>();

	// vec3(0.5f) is block offset, so first block is on vec3(0, 0, 0)
	batch.model->set_translation(workspace.chunk->get_position() + vec3(0.5f));
	batch.model->use(true);

	batch.model->add_vbo(3, batch.vertices);
	batch.model->add_vbo(2, batch.texture_coordinates);
	batch.model->add_vbo(1, batch.light_levels);
	batch.model->add_ebo(batch.indices);

	batch.model->use(false);
}