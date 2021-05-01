#include "cave_generator.h"

#include "application/common/defines.h"

using namespace	game;

				cave_generator::cave_generator() : noise(FT_VOX_SEED, 0.02f)
{}

bool 			cave_generator::operator () (const vec3 &position)
{
	if (position.y == 0)
		return false;

	return noise(position) < 0.22f;
}
