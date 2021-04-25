#include "biome_generator.h"

#include "application/common/debug/debug.h"

using namespace					game;

shared_ptr<biomes::abstract>	biome_generator::generate_biome(const vec2 &column)
{
	const auto 					shift_x = noise_for_cell_shift.generate({column.x, column.y});
	const auto 					shift_y = noise_for_cell_shift.generate({column.y, column.x});
	const auto					shift = vec2(shift_x, shift_y);

	const auto					cell = noise_for_cell.generate(column + shift);
	const auto					biome_noise = noise_for_selection.generate_1d(cell.position);

	return select_biome(biome_noise);
}

void 							biome_generator::updated_ranges()
{
	float						total_wight = 0.f;
	float						last_max = 0;

	for (const auto &biome_with_range : biome_configs)
		total_wight += biome_with_range.weight;

	for (auto &biome_with_range : biome_configs)
	{
		biome_with_range.min = last_max;
		biome_with_range.max = biome_with_range.min + biome_with_range.weight / total_wight;

		last_max = biome_with_range.max;
	}
}

shared_ptr<biomes::abstract>		biome_generator::select_biome(float value)
{
	for (const auto &biome_with_range : biome_configs)
	{
		if (value >= biome_with_range.min and value < biome_with_range.max)
			return biome_with_range.biome;
	}

	debug::raise_error("[biome_manager] Biome not found");
	return nullptr;
}
