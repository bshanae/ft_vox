#pragma once

#include "engine/core/object/unique_object/unique_object.h"

#include "game/world/chunk/generator/biome/biome_collection/biome_collection.h"

#include "application/common/imports/std.h"
#include "application/common/imports/glm.h"
#include "FastNoiseLite.h"

namespace						game
{
	class						chunk;

	class						generator;
}

class							game::generator : public engine::unique_object<generator>
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


