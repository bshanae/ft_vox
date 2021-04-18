#include "biome_collection.h"

#include "application/common/debug/debug.h"

using namespace 	game;

					biome_collection::biome_collection()
{
	collection.emplace(biome::dirt, biome(biome::dirt));
    collection.emplace(biome::grass, biome(biome::grass));
    collection.emplace(biome::sand, biome(biome::sand));
	collection.emplace(biome::stone, biome(biome::stone));
}

const biome			&biome_collection::get_biome(enum biome::type type) const
{
	const auto		iterator = collection.find(type);

	debug::check_critical(iterator != collection.cend(), "[biome_collection] Can't find biome");
	return iterator->second;
}