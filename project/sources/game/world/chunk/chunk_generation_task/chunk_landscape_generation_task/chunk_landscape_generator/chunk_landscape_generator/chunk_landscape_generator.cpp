#include "chunk_landscape_generator.h"

#include "game/world/chunk/chunk/chunk.h"

using namespace			game;

						chunk_landscape_generator::chunk_landscape_generator()
{
	int seed = 133929;
	biome_collection::construct();
	noise_for_biome = cellular_noise(0.008f, seed);
	perlin = perlin_noise(seed, 0.01f, 150.f);
	perlinCloud = perlin_noise(seed, 0.03f);
	perlin3d = perlin_noise(seed, 0.03f);
}

float					chunk_landscape_generator::smoothing_height(const ivec2 &position)
{
    const auto			instance = get_instance();

    float               height = 0.f;
    float               weight;
    float               total_weight = 0.f;

    for (int x = -8; x <= 8; x += 2)
    for (int y = -8; y <= 8; y += 2)
    {
        vec2            heighboring = (vec2)position + vec2(x, y);

        float           perlin_shift = instance->perlin.generate(heighboring);
        const auto      column = instance->noise_for_biome.generate(heighboring + perlin_shift);
        weight = 1.f - (1.f / (1.f + abs((float)x) + abs((float)y)));

        height += instance->choose_biome(column.noise_value).generate_height(heighboring + perlin_shift) * weight;
        total_weight += weight;
    }

    height /= total_weight;

    return (height);
}

						chunk_landscape_generator::column_info
						chunk_landscape_generator::
						generate_column(const ivec2 &position)
{
    const auto			instance = get_instance();

    float               perlin_shift = instance->perlin.generate(position);
    const auto			&nearest = instance->noise_for_biome.generate((vec2)position + perlin_shift);

    int                 zero_height = 62;
    int                 height = (int)floor(smoothing_height(position)) + zero_height;

	return {instance->choose_biome(nearest.noise_value), height};
}

void                    chunk_landscape_generator::generation_clouds(const shared_ptr<chunk> &chunk, vec3 position, chunk::index index)
{
    if (get_instance()->perlinCloud.generate({position.x, position.z}) > 0.7f)
    {
        index.y = 150;

        chunk->at(index).set_type(block_type::water);
    }
}

void					chunk_landscape_generator::generate_chunk(const shared_ptr<chunk> &chunk)
{
    const int           zero_height = 62;
    const int	        water_level = zero_height + -3;

	const vec3			position_chunk = chunk->get_position();

	chunk::index		index;

	for (index.x = 0; index.x < chunk_settings::size[0]; index.x++)
	for (index.z = 0; index.z < chunk_settings::size[2]; index.z++)
	{
	    vec3            position = vec3(position_chunk.x + (float)index.x, 0, position_chunk.z + (float)index.z);
		const auto		column_info = generate_column({position.x, position.z});
		const auto		block_type = (enum block_type)column_info.biome.get_first_layer();
        int		        height_limit = min(chunk_settings::size[1], max(water_level, column_info.height));

		for (index.y = 0; index.y < height_limit; index.y++)
		{
		    position.y = index.y;
            if (index.y > 0 && index.y < column_info.height - 15) {
                generation_dungeons(chunk, index, position, block_type);
            }
            else if (index.y <= column_info.height)
				chunk->at(index).set_type(block_type);
            else if (index.y < zero_height)
                chunk->at(index).set_type(block_type::water);
		}

		generation_clouds(chunk, position, index);
	}

}

void                    chunk_landscape_generator::generation_dungeons(const shared_ptr<chunk> &chunk, chunk::index index, vec3 position, block_type block_type)
{
    const auto			instance = get_instance();

    if (instance->perlin3d.generate3d(position) < 0.25f)
        chunk->at(index).set_type(block_type::air);
    else
        chunk->at(index).set_type(block_type);
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