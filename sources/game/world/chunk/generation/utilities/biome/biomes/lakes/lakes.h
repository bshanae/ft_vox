#pragma once

#include "game/world/chunk/generation/utilities/biome/biomes/abstract/abstract.h"
#include "game/world/chunk/generation/utilities/height_generator/height_generator.h"

namespace					game::biomes
{
	class 					lakes;
}
class						game::biomes::lakes : public game::biomes::abstract
{
public :
							lakes();
							~lakes() override = default;

	int						generate_height(const vec2 &column) const override;
	block_type				generate_block(int current_height, int total_height, bool is_cave, bool is_cloud) const override;
	void					generate_decoration(const block_ptr &block, bool is_height_affected_by_cave) const override;

private :

	static constexpr int	water_level = chunk_settings::zero_height - 2;

	height_generator		height_generator;

	static block_type		generate_block_in_cave(int current_height, int total_height);
	static block_type		generate_empty_block(int current_height, int total_height);
	static block_type		generate_solid_block(int current_height, int total_height);
};