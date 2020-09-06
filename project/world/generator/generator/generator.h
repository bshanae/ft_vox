#pragma once

#include "FastNoise.h"

#include "common/aliases.h"
#include "common/glm.h"
#include "engine/object/unique_object/unique_object.h"
#include "world/generator/biome/biome_collection.h"

namespace						world
{
	class						chunk;

	class						generator;
}

class							world::generator : public engine::unique_object<generator>
{
public :
								generator();
								~generator() override = default;


	static void					generate(const shared_ptr<chunk> &chunk);

private :

	struct
	{
		vec3					position;

		biome					biome;
		int						height;
	}							workspace;

	cellular_noise				noise_for_biome;

	biome						biome(const vec3 &position);
	optional<::world::biome>	neighbor_biome(const vec3 &direction);

	void						process_column(const vec3 &position);
};


