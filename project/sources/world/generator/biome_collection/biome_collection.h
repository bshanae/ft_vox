#pragma once

#include "common/imports/std.h"
#include "engine/object/unique_object/unique_object.h"
#include "world/generator/biome/biome.h"

namespace				world
{
	class				biome_collection;
}

class 					world::biome_collection : public engine::unique_object<biome_collection>
{
public :
						biome_collection();
						~biome_collection() override = default;

	const biome			&get_biome(enum biome::type type);

private :
						unordered_map<enum biome::type, ::world::biome>
						collection;
};