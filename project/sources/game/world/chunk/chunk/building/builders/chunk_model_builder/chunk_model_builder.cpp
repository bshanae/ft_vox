#include "chunk_model_builder.h"

#include "engine/main/rendering/model/model/model.h"

#include "game/world/chunk/chunk/building/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/chunk/chunk/chunk.h"

using namespace		game;

void				chunk_model_builder::launch(const shared_ptr<chunk_workspace> &workspace)
{
	debug::check_critical
	(
		workspace->state == chunk_workspace::geometry_done,
		"[chunk_model_builder] Chunk workspace has unexpected state"
	);

	workspace->state = chunk_workspace::model_in_process;

	process_batch(workspace, workspace->batch_for_opaque);
	process_batch(workspace, workspace->batch_for_transparent);
	process_batch(workspace, workspace->batch_for_partially_transparent);

	workspace->state = chunk_workspace::model_done;
}

void				chunk_model_builder::process_batch
					(
						const shared_ptr<chunk_workspace> &workspace,
						chunk_workspace::batch &batch
					)
{
	batch.model = make_shared<engine::model>();

	// vec3(0.5f) is block offset, so first block is on vec3(0, 0, 0)
	batch.model->set_translation(workspace->chunk->get_position() + vec3(0.5f));
	batch.model->use(true);

	batch.model->add_vbo(3, batch.vertices);
	batch.model->add_vbo(2, batch.texture_coordinates);
	batch.model->add_vbo(1, batch.light_levels);
	batch.model->add_ebo(batch.indices);

	batch.model->use(false);
}