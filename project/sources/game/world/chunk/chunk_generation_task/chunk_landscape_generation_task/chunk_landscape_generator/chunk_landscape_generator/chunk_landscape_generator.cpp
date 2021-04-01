#include "chunk_landscape_generator.h"

#include "game/world/chunk/chunk/chunk.h"

using namespace			game;

						chunk_landscape_generator::chunk_landscape_generator()
{
	biome_collection::construct();
	noise_for_biome = cellular_noise(0.01f);
	perlin = perlin_noise(1.f, 0.01f, 150.f);
}

						chunk_landscape_generator::column_info
						chunk_landscape_generator::generate_column(const ivec2 &position)
{
	const auto			instance = get_instance();
	const auto			result = instance->noise_for_biome.generate(position);

	const auto 			&nearest = result.nearest;
	const auto 			&furthest = result.furthest;

	const auto			&central_cell = result.central;
	const auto			&left_cell = result.left;
	const auto			&right_cell = result.right;
	const auto			&top_cell = result.top;
	const auto			&bottom_cell = result.bottom;
	const auto			&top_left_cell = result.top_left;
	const auto			&top_right_cell = result.top_right;
	const auto			&bottom_left_cell = result.bottom_left;
	const auto			&bottom_right_cell = result.bottom_right;

	/*const auto			central_cell_height = instance->choose_biome(central_cell.noise_value).generate_height(position);
	const auto			left_cell_height = instance->choose_biome(left_cell.noise_value).generate_height(position);
	const auto			right_cell_height = instance->choose_biome(right_cell.noise_value).generate_height(position);
	const auto			top_cell_height = instance->choose_biome(top_cell.noise_value).generate_height(position);
	const auto			bottom_cell_height = instance->choose_biome(bottom_cell.noise_value).generate_height(position);
	const auto			top_left_cell_height = instance->choose_biome(top_left_cell.noise_value).generate_height(position);
	const auto			top_right_cell_height = instance->choose_biome(top_right_cell.noise_value).generate_height(position);
	const auto			bottom_left_cell_height = instance->choose_biome(bottom_left_cell.noise_value).generate_height(position);
	const auto			bottom_right_cell_height = instance->choose_biome(bottom_right_cell.noise_value).generate_height(position);

	const float			central_cell_influence = 1.f - central_cell.distance / furthest.distance;
	const float			left_cell_influence = 1.f - left_cell.distance / furthest.distance;
	const float			right_cell_influence = 1.f - right_cell.distance / furthest.distance;
	const float			top_cell_influence = 1.f - top_cell.distance / furthest.distance;
	const float			bottom_cell_influence = 1.f - bottom_cell.distance / furthest.distance;
	const float			top_left_cell_influence = 1.f - top_left_cell.distance / furthest.distance;
	const float			top_right_cell_influence = 1.f - top_right_cell.distance / furthest.distance;
	const float			bottom_left_cell_influence = 1.f - bottom_left_cell.distance / furthest.distance;
	const float			bottom_right_cell_influence = 1.f - bottom_right_cell.distance / furthest.distance;

	const float			total_influence =
							central_cell_influence
							+ left_cell_influence
							+ right_cell_influence
							+ top_cell_influence
							+ bottom_cell_influence
							+ top_left_cell_influence
							+ top_right_cell_influence
							+ bottom_left_cell_influence
							+ bottom_right_cell_influence;

	float				height = 0.f;

	height += central_cell_height * central_cell_influence;
	height += left_cell_height * left_cell_influence;
	height += right_cell_height * right_cell_influence;
	height += top_cell_height * top_cell_influence;
	height += bottom_cell_height * bottom_cell_influence;
	height += top_left_cell_height * top_left_cell_influence;
	height += top_right_cell_height * top_right_cell_influence;
	height += bottom_left_cell_height * bottom_left_cell_influence;
	height += bottom_right_cell_height * bottom_right_cell_influence;

	height /= total_influence;*/

	return {instance->choose_biome(nearest.noise_value), (int)floor(0.f)};
}

void					chunk_landscape_generator::generate_chunk(const shared_ptr<chunk> &chunk)
{

	static const int	water_level = 10;

    const auto			instance = get_instance();
	const vec3			position = chunk->get_position();

	chunk::index		index;

	for (index.x = 0; index.x < chunk_settings::size[0]; index.x++)
	for (index.z = 0; index.z < chunk_settings::size[2]; index.z++)
	{
	    const auto      input = vec3(position.x + (float)index.x, 0, position.z + (float)index.z);
        const auto      perlin_shift = abs(instance->perlin.generate(vec2(input.x, input.z)));
        const auto		column_position = vec3(input.x + perlin_shift, 0, input.z + perlin_shift);
		const auto		column_info = generate_column({column_position.x, column_position.z});
		const auto		block_type = (enum block_type)column_info.biome.get_first_layer();
		const auto		height_limit = min(chunk_settings::size[1], max(water_level, column_info.height));

		for (index.y = 0; index.y < 1; index.y++)
		{
			if (index.y <= column_info.height)
				chunk->at(index).set_type(block_type);
			else if (index.y <= water_level)
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