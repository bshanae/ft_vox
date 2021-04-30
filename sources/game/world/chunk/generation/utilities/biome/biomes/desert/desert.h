#pragma once

#include "game/world/chunk/generation/utilities/biome/biomes/abstract/abstract.h"
#include "game/world/chunk/generation/utilities/height_generator/height_generator.h"
#include "game/world/chunk/generation/utilities/decoration_generator/decoration_generator.h"

namespace					game::biomes
{
	class 					desert;
}

class						game::biomes::desert : public game::biomes::abstract
{
public :

							desert();
							~desert() override = default;

	int						generate_height(const vec2 &column) const override;
	block_type				generate_block(int current_height, int total_height, bool is_cave, bool is_cloud) const override;
	void					generate_decoration(const block_ptr &block, bool is_height_affected_by_cave) const override;

private :

	height_generator		height_generator;
	decoration_generator	decoration_generator;
};