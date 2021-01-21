#include "biome_collection.h"

using namespace 	game;

					biome_collection::biome_collection()
{
	set_layout("System");

	collection.emplace(biome::test_dirt, biome(biome::test_dirt));
	collection.emplace(biome::test_stone, biome(biome::test_stone));
}

const biome			&biome_collection::get_biome(enum biome::type type)
{
	const auto		instance = get_instance();
	auto			iterator = instance->collection.find(type);

	assert(iterator != instance->collection.end());
	return iterator->second;
}