#include "biome_collection.h"

using namespace 	world;

					biome_collection::biome_collection()
{
	object::layout = "System";
	object::should_be_rendered = false;
	object::should_be_updated = false;

	collection.emplace(biome::test_dirt, ::world::biome(biome::test_dirt));
	collection.emplace(biome::test_stone, ::world::biome(biome::test_stone));
}

const biome			&biome_collection::get_biome(enum biome::type type)
{
	auto			iterator = collection.find(type);

	assert(iterator != collection.end());
	return (iterator->second);
}