#pragma once

#include "application/common/imports/std.h"
#include "application/common/imports/glm.h"
#include "application/common/defines.h"

#include "game/world/chunk/generation/utilities/noise/cellular_noise.h"
#include "game/world/chunk/generation/utilities/noise/perlin_noise_2d.h"
#include "game/world/chunk/generation/utilities/biome/biomes/abstract/abstract.h"

namespace									game
{
	class 									biome_generator;
}

class										game::biome_generator
{
public :

	template								<typename T>
	static void								register_biome(float weight)
	{
		static_assert(std::is_base_of<biomes::abstract, T>::value, "Given type is not derived from 'biomes::abstract'");

		biome_configs.push_back({make_shared<T>(), weight, 0, 0});
		updated_ranges();
	}

	static shared_ptr<biomes::abstract>		generate_biome(const vec2 &column);

private :

	struct									biome_config
	{
		const shared_ptr<biomes::abstract>	biome;
		const float							weight;

		float								min;
		float								max;
	};

	static inline cellular_noise			noise_for_cell{FT_VOX_SEED, 0.002f};
	static inline perlin_noise_2d			noise_for_cell_shift{FT_VOX_SEED, 0.02f, 50.f};
	static inline random_noise_1d			noise_for_selection{FT_VOX_SEED};

	static inline list<biome_config>		biome_configs = {};

	static void 							updated_ranges();
	static shared_ptr<biomes::abstract>		select_biome(float value);
};