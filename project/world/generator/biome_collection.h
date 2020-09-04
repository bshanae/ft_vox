#pragma once

#include "common/aliases.h"
#include "world/generator/biome.h"

class 					biome_collection : public unique_object<biome_collection>
{
public :
						biome_collection()
	{
		object::layout = "System";
		object::should_be_rendered = false;
		object::should_be_updated = false;

		collection.emplace(biome::test_dirt, ::biome(biome::test_dirt));
		collection.emplace(biome::test_stone, ::biome(biome::test_stone));
	}
						~biome_collection() override = default;

	static const biome	&biome(enum biome::type type)
	{
		auto			instance = unique_object::instance();
		auto			iterator = instance->collection.find(type);

		assert(iterator != instance->collection.end());
		return (iterator->second);
	}

private :

						unordered_map<enum biome::type, ::biome>
						collection;
};