#include "height_generator.h"

#include "application/common/defines.h"

#include "game/world/chunk/chunk/chunk_settings.h"

using namespace		game;

					height_generator::height_generator(float frequency, float multiplier) :
						noise(FT_VOX_SEED, frequency, multiplier)
{}

int 				height_generator::operator () (const vec2 &column) const
{
	return chunk_settings::zero_height + (int)noise.generate(column);
}