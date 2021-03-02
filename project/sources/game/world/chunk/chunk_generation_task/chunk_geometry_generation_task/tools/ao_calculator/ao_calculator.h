#pragma once

#include "game/world/block/block_face/block_face.h"
#include "game/world/chunk/chunk/chunk.h"

namespace							game
{
	class 							block_ptr;
	class 							ao_calculator;
}

class 								game::ao_calculator
{
public :

	static array<float, 4>			calculate(const block_ptr &block, block_face face);

private :

	using							occluder_offsets_type = const chunk::index (&)[3];
	using							occluders_offsets_type = const chunk::index (&)[4][3];

	static occluders_offsets_type	get_occluders_offsets(block_face face);
	static float 					calculate(const block_ptr &block, occluder_offsets_type occluder_offsets);
};