#pragma once

#include "application/common/imports/glm.h"
#include "game/world/chunk/generation/utilities/noise/perlin_noise_2d.h"

namespace			game
{
	class			height_generator;
}

class				game::height_generator
{
public :
					height_generator(float frequency, float multiplier);
	int 			operator () (const vec2 &column) const;

private :

	perlin_noise_2d	noise;
};
