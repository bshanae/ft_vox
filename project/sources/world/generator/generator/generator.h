#pragma once

#include "FastNoiseLite.h"

#include "common/imports/std.h"
#include "common/imports/glm.h"
#include "engine/object/unique_object/unique_object.h"
#include "world/generator/biome_collection/biome_collection.h"

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

	void						process_column(const vec3 &position);

	const biome					&choose_biome(float noise_value);
};


