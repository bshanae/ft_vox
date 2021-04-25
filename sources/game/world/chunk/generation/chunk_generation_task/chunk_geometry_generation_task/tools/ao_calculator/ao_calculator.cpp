#include "ao_calculator.h"

#include "game/world/block/block_ptr/block_ptr.h"
#include "game/world/chunk/generation/chunk_generation_task/chunk_geometry_generation_task/data/occluders_offsets.h"

using namespace							game;

array<float, 4>							ao_calculator::calculate(const block_ptr &block, block_face face)
{
	occluders_offsets_type				occluders_offsets = get_occluders_offsets(face);
	array<float, 4>						ao_values = {};

	for (int i = 0; i < 4; i++)
		ao_values[i] = calculate(block, occluders_offsets[i]);

	return ao_values;
}

ao_calculator::occluders_offsets_type	ao_calculator::get_occluders_offsets(block_face face)
{
	switch (face)
	{
		case block_face::left:
			return left_occluders_offsets;

		case block_face::right:
			return right_occluders_offsets;

		case block_face::front:
			return front_occluders_offsets;

		case block_face::back:
			return back_occluders_offsets;

		case block_face::top:
			return top_occluders_offsets;

		case block_face::bottom:
			return bottom_occluders_offsets;

		default:
			debug::raise_error("Unexpected code branch");
	}
}

float									ao_calculator::calculate(const block_ptr &block, occluder_offsets_type occluder_offsets)
{
	int									count = 0;
	block_ptr							neighbor_block;

	for (const auto &occluder_offset : occluder_offsets)
	{
		neighbor_block = block.get_neighbor(occluder_offset);
		count += neighbor_block != nullptr and not does_transmit_light(get_meta_type(neighbor_block->get_type()));
	}

	return (float)count / 3;
}