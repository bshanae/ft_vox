#include "generator.h"

#include "world/chunk/chunk.h"

using namespace			world;

						generator::generator()
{
	object::layout = "System";
	object::should_be_updated = false;
	object::should_be_rendered = false;

	noise_for_biome.SetNoiseType(FastNoise::Cellular);
	noise_for_biome.SetFrequency(0.005);
	noise_for_biome.SetCellularReturnType(FastNoise::CellValue);
	noise_for_biome.SetCellularDistanceFunction(FastNoise::Natural);
}

void					generator::generate(const shared_ptr<chunk> &chunk)
{
	static const int	water_level = 10;

	auto 				instance = generator::instance();
	const vec3			position = chunk->position;

	chunk::index		index;

	for (index.x = 0; index.x < chunk_settings::size[0]; index.x++)
		for (index.z = 0; index.z < chunk_settings::size[2]; index.z++)
		{
			instance->process_column(vec3(position.x + index.x, 0, position.z + index.z));

			const auto	&workspace = instance->workspace;

			const auto	block_type = (enum block::type)workspace.biome.first_layer;
			const auto	height_limit = min(chunk_settings::size[1], max(water_level, workspace.height));

			for (index.y = 0; index.y < height_limit; index.y++)
				if (index.y <= workspace.height)
					chunk->at(index).type = block_type;
				else if (index.y <= water_level)
					chunk->at(index).type = block::water;
		}
}

biome					generator::biome(const vec3 &position)
{
	float				value = noise_for_biome.GetNoise(position.x, position.z);

	if (value > 0)
		return (biome_collection::biome(biome::test_dirt));
	else
		return (biome_collection::biome(biome::test_stone));
}

optional<biome>			generator::neighbor_biome(const vec3 &direction)
{
	static const float	step_distance = 2;
	static const int	step_limit = 10;

	vec3				iterator = workspace.position;
	vec3				step = direction * step_distance;

	for (int count = 0; count < step_limit; count++)
	{
		iterator += step;
		if (auto neighbor = biome_collection::biome(biome::test_dirt); neighbor != workspace.biome)
			return {neighbor};
	}

	return {};
}

void					generator::process_column(const vec3 &position)
{
	static auto			height_of_neighbor_biome = [this](const vec3 &direction)
	{
		auto			neighbor = generator::neighbor_biome(direction);

		if (neighbor)
			return (optional<float>(neighbor->height(workspace.position)));
		else
			return (optional<float>());
	};

	workspace.position = position;
	workspace.biome = biome(position);
	workspace.height = workspace.biome.height(position);
}