#pragma once

#include "application/common/imports/std.h"

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

#include "game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generator/biome/biome/biome.h"

namespace									game
{
	class									biome_collection;
}

class 										game::biome_collection : public singleton<biome_collection>
{
public :
											biome_collection();
											~biome_collection() override = default;

	const biome								&get_biome(enum biome::type type) const;

private :

	unordered_map<enum biome::type, biome>	collection;
};