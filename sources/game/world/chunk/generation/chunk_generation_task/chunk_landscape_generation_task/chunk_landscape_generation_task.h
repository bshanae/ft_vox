#pragma once

#include "application/common/imports/glm.h"
#include "game/world/chunk/chunk/chunk.h"
#include "game/world/chunk/generation/utilities/biome/biomes/abstract/abstract.h"
#include "game/world/chunk/generation/chunk_generation_task/chunk_generation_task/chunk_generation_task.h"
#include "game/world/chunk/generation/utilities/cave_generator/cave_generator.h"

namespace							game
{
	class							chunk_landscape_generation_task;
}

class								game::chunk_landscape_generation_task : public game::chunk_generation_task
{
public :
									chunk_landscape_generation_task();
									~chunk_landscape_generation_task() override = default;
protected :

	static inline cave_generator	cave_generator;

	void 							do_launch(chunk_workspace &workspace) override;

	static void						generate_chunk(chunk_workspace &workspace);
	static void						generate_column(chunk_workspace &workspace, chunk::index index);

	static void						save_calculated_info
									(
										chunk_workspace &workspace,
										chunk::index index,
										const shared_ptr<biomes::abstract> &biome,
										int final_height,
										int is_height_affected_by_cave
									);
};