#pragma once

#include "engine/core/object/unique_object/unique_object.h"

#include "game/world/chunk/generator/biome/biome/biome.h"

#include "application/common/imports/std.h"

namespace				game
{
	class				biome_collection;
}

class 					game::biome_collection : public engine::unique_object<biome_collection>
{
public :
						biome_collection();
						~biome_collection() override = default;

	const biome			&get_biome(enum biome::type type);

private :
						unordered_map<enum biome::type, biome>
						collection;
};