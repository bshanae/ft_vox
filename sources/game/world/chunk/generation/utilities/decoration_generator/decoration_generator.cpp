#include "decoration_generator.h"

#include "application/common/defines.h"

using namespace	game;

				decoration_generator::decoration_generator(float frequency) : noise(FT_VOX_SEED, frequency)
{}

bool 			decoration_generator::operator () (const vec2 &column) const
{
	return noise(column) > 0.95f;
}