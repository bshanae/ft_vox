#include "cloud_generator.h"

#include "application/common/defines.h"

using namespace	game;

				cloud_generator::cloud_generator() : noise(FT_VOX_SEED, 0.03f)
{}

bool 			cloud_generator::operator () (const vec3 &position)
{
	if (position.y != 180)
		return false;

	return noise({position.x, position.z}) > 0.65f;
}
