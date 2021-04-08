#include "chunk_landscape_generator.h"

#include "game/world/chunk/chunk/chunk.h"

using namespace			game;

						chunk_landscape_generator::chunk_landscape_generator()
{
	int seed = 13;
	biome_collection::construct();
	noise_for_biome = cellular_noise(0.008f, seed);
	perlin = perlin_noise(seed, 0.01f, 150.f);
}

						chunk_landscape_generator::column_info
						chunk_landscape_generator::
						generate_column(const ivec2 &position)
{
    const auto			instance = get_instance();

    float               perlin_shift = instance->perlin.generate(position);
    const auto			&nearest = instance->noise_for_biome.generate((vec2)position + perlin_shift);

	float               height = 0.f;
	float               weight;
	float               total_weight = 0.f;

    for (int x = -12; x <= 12; x += 3)
    for (int y = -12; y <= 12; y += 3)
    {
        vec2            heighboring = (vec2)position + vec2(x, y);

        perlin_shift = instance->perlin.generate(heighboring);
        const auto      column = instance->noise_for_biome.generate(heighboring + perlin_shift);
        weight = 1.f / (1.f + abs((float)x) + abs((float)y));

        height += instance->choose_biome(column.noise_value).generate_height(heighboring + perlin_shift) * weight;
        total_weight += weight;
    }

    height /= total_weight;

	return {instance->choose_biome(nearest.noise_value), (int)floor(height)};
}

void					chunk_landscape_generator::generate_chunk(const shared_ptr<chunk> &chunk)
{
    const int	water_level = -3;
    const int   zero_height = 124 + water_level;

	const vec3			position = chunk->get_position();

	chunk::index		index;

	for (index.x = 0; index.x < chunk_settings::size[0]; index.x++)
	for (index.z = 0; index.z < chunk_settings::size[2]; index.z++)
	{
		const auto		column_info = generate_column({position.x + (float)index.x, position.z + (float)index.z});
		const auto		block_type = (enum block_type)column_info.biome.get_first_layer();
		const auto		height_limit = min(chunk_settings::size[1], max(water_level, column_info.height)) + zero_height;

		for (index.y = 0; index.y < height_limit; index.y++)
		{
			if (index.y <= column_info.height + zero_height)
				chunk->at(index).set_type(block_type);
			else if (index.y <= zero_height)
				chunk->at(index).set_type(block_type::water);
		}
	}

}

const biome				&chunk_landscape_generator::choose_biome(float noise_value)
{
	if (noise_value > 0.9f)
		return (biome_collection::get_instance()->get_biome(biome::stone));
	else if (noise_value > 0.8f)
		return (biome_collection::get_instance()->get_biome(biome::sand));
	else if (noise_value > 0.6f)
		return (biome_collection::get_instance()->get_biome(biome::rock));
	else if (noise_value > 0.3f)
		return (biome_collection::get_instance()->get_biome(biome::grass));
	return (biome_collection::get_instance()->get_biome(biome::dirt));
}