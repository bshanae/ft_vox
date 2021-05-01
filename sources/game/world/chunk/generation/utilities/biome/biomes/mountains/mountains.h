#pragma once

#include "game/world/chunk/generation/utilities/biome/biomes/abstract/abstract.h"
#include "game/world/chunk/generation/utilities/height_generator/height_generator.h"
#include "game/world/chunk/generation/utilities/decoration_generator/decoration_generator.h"

namespace					game::biomes
{
	class 					mountains;
}
class						game::biomes::mountains : public game::biomes::abstract
{
public :
							mountains();
							~mountains() override = default;

	int						generate_height(const vec2 &column) const override;
	block_type				generate_block(int current_height, int total_height, bool is_cave, bool is_cloud) const override;
	void					generate_decoration(const block_ptr &block, bool is_height_affected_by_cave) const override;

private :

	static inline int 		snow_level = 105;

	height_generator		height_generator;
	decoration_generator	snow_generator;

	bool					should_replace_stone_with_snowy_stone(const block_ptr &block) const;
	void					replace_stone_with_snowy_stone(const block_ptr &block) const;
};