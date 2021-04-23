#include "chunk_landscape_generator.h"

#include "game/world/chunk/chunk/chunk.h"

using namespace			game;

						chunk_landscape_generator::chunk_landscape_generator()
{
	biome_collection::construct();

    seed = 13;

	noise_for_cell = cellular_noise(chunk_settings::landscape_seed, 0.003f);
	noise_for_cell_shift = perlin_noise(chunk_settings::landscape_seed, 0.01f, 50.f);
	noise_for_biome = random_noise();
    noise_for_snow = perlin_noise(chunk_settings::landscape_seed, 0.07f);
	noise_for_clouds = perlin_noise(chunk_settings::landscape_seed, 0.03f);
	noise_for_dungeons = perlin_noise(chunk_settings::landscape_seed, 0.03f);

	noise_for_mushroom = perlin_noise(chunk_settings::landscape_seed, 0.07f);
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

            if (index.y <= column_info.height) {
                if (index.y > zero_height + 45) {
                    if (index.y == column_info.height - 1
                        && chunk->at({index.x, index.y - 1, index.z}).get_type() != block_type::air) {
                        if (index.y <= zero_height + 55) {
                            if (get_instance()->noise_for_snow.generate({position.x + position.z, position.y}) > 0.5f) {
                                chunk->at(index).set_type(block_type::snow);
                            }
                            else
                                generation_dungeons(chunk, index, position, block_type);
                        }
                        else
                            chunk->at(index).set_type(block_type::snow);
                    }
                    else
                        generation_dungeons(chunk, index, position, block_type);
                }
                else
                    generation_dungeons(chunk, index, position, block_type);
            }
            else if (index.y < zero_height)
                chunk->at(index).set_type(block_type::water);
        }

		generation_flora(chunk, position, index, block_type);
		generation_clouds(chunk, position, index);
	}
}

						chunk_landscape_generator::column_info
						chunk_landscape_generator::
						generate_column(const ivec2 &position)
{
    const auto			instance = get_instance();

    float               perlin_cell_shift = instance->noise_for_cell_shift.generate(position);
    const auto			&cell = instance->noise_for_cell.generate((vec2)position + perlin_cell_shift);

    const int			zero_height = 62;
    const int			height = (int)floor(smoothing_height(position)) + zero_height;

	return { instance->generate_biome(cell.position), height };
}

float					chunk_landscape_generator::smoothing_height(const ivec2 &position)
{
	const auto			instance = get_instance();

	float               height = 0.f;
	float               total_weight = 0.f;

	for (int x = -8; x <= 8; x += 2)
	for (int y = -8; y <= 8; y += 2)
	{
		const auto		height_of_neighbor = (vec2)position + vec2(x, y);
		const auto		perlin_shift = instance->noise_for_cell_shift.generate(height_of_neighbor);
		const auto      column = instance->noise_for_cell.generate(height_of_neighbor + perlin_shift);
		const auto		weight = 1.f - 1.f / (1.f + (float)abs(x) + (float)abs(y));

		height += (float)instance->generate_biome(column.position).generate_height(height_of_neighbor + perlin_shift) * weight;
		total_weight += weight;
	}

	height /= total_weight;

	return height;
}

void                    chunk_landscape_generator::generation_clouds(const shared_ptr<chunk> &chunk, vec3 position, chunk::index index)
{
    if (get_instance()->noise_for_clouds.generate({position.x, position.z}) > 0.7f)
    {
        index.y = 150;
        chunk->at(index).set_type(block_type::cloud);
    }
}

void                    chunk_landscape_generator::generation_flora(const shared_ptr<chunk> &chunk, vec3 position, chunk::index index, block_type block_type)
{
    if (chunk->at({index.x, index.y - 1, index.z}).get_type() != block_type::air) {
        if (block_type == block_type::dirt) {
            if (get_instance()->noise_for_mushroom.generate({position.x, position.z}) > 0.95f)
                chunk->at(index).set_type(block_type::mushroom);
        }
//        if (block_type == block_type::dirt) {
//            if ((int)position.x % 7 == 0 && (int)position.z % 7 == 0)
//                if (get_instance()->noise_for_mushroom.generate({position.x, position.z}) > 0.80f)
//                    generation_tree(chunk, index);
//        }
    }
}

void                    chunk_landscape_generator::generation_tree(const shared_ptr<chunk> &chunk, chunk::index index)
{

//    while (index.y < height) {
//        chunk->at(index).set_type(block_type::snow);
//        if (height - index.y > 3)
//
//        index.y++;
//    }
    int height = 7;

    for (int y = 0; y < height; y++) {
        chunk->at(index).set_type(block_type::snow);

//        int test = height - y;
//        if (test % 2 == 0 && test > 5) {
//            for (int x = -test; x < height; x++)
//            for (int z = -test; z < height; z++) {
//                chunk->at({index.x + x, index.y, index.z + z}).set_type(block_type::grass);
//            }
//        }

//        if (7 - y > 0) {
//            for (int x = -(7 - y); x < 7 - y; x++)
//            for (int z = -(7 - y); z < 7 - y; z++) {
//
//                chunk->at({index.x + x, index.y, index.z + z}).set_type(block_type::grass);
//            }
//        }
        index.y++;
    }
}

void                    chunk_landscape_generator::generation_dungeons(const shared_ptr<chunk> &chunk, chunk::index index, vec3 position, block_type block_type)
{
    const auto			instance = get_instance();

    if (instance->noise_for_dungeons.generate_3d(position) < 0.25f)
        chunk->at(index).set_type(block_type::air);
    else
        chunk->at(index).set_type(block_type);
}

const biome				&chunk_landscape_generator::generate_biome(const vec2 &cell_position)
{
	const float			noise = noise_for_biome.generate_1d(cell_position, seed);

	if (noise > 0.6f)
		return biome_collection::get_instance()->get_biome(biome::stone);
	else if (noise > 0.4f)
		return biome_collection::get_instance()->get_biome(biome::sand);
	else if (noise > 0.2f)
		return biome_collection::get_instance()->get_biome(biome::grass);

	return biome_collection::get_instance()->get_biome(biome::dirt);
}