#include "biome_collection.h"

#include "application/common/debug/debug.h"

using namespace 	game;

					biome_collection::biome_collection()
{
	collection.emplace(biome::test_dirt, biome(biome::test_dirt));
	collection.emplace(biome::test_stone, biome(biome::test_stone));
}

const biome			&biome_collection::get_biome(enum biome::type type) const
{
	const auto		iterator = collection.find(type);

	debug::check_critical(iterator != collection.cend(), "[biome_collection] Can't find biome");
	return iterator->second;
}