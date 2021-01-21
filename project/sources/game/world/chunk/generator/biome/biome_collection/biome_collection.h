#pragma once

#include "engine/core/object/object/object.h"
#include "engine/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

#include "game/world/chunk/generator/biome/biome/biome.h"

#include "application/common/imports/std.h"

namespace				game
{
	class				biome_collection;
}

class 					game::biome_collection :
							public engine::object,
							public engine::unique_object_constructor<biome_collection>
{
public :
						biome_collection();
						~biome_collection() override = default;

	static const biome	&get_biome(enum biome::type type);

private :
						unordered_map<enum biome::type, biome>
						collection;
};