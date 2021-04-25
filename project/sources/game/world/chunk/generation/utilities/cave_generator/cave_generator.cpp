#include "cave_generator.h"

#include "application/common/defines.h"

using namespace	game;

				cave_generator::cave_generator() : noise(FT_VOX_SEED, 0.015f)
{}

bool 			cave_generator::operator () (const vec3 &position)
{
	return noise.generate_3d(position) < 0.25f;
}
