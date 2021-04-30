#pragma once

#include "game/world/chunk/generation/utilities/noise/perlin_noise_2d.h"

namespace			game
{
	class			cloud_generator;
}

class				game::cloud_generator
{
public :
					cloud_generator();
	bool 			operator () (const vec3 &position);

private :

	perlin_noise_2d	noise;
};