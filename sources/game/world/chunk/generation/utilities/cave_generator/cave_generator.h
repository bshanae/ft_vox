#pragma once

#include "game/world/chunk/generation/utilities/noise/perlin_noise_3d.h"

namespace			game
{
	class			cave_generator;
}

class				game::cave_generator
{
public :
					cave_generator();
	bool 			operator () (const vec3 &position);

private :

	perlin_noise_3d	noise;
};