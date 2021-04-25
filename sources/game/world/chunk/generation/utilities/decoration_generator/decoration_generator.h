#pragma once

#include "game/world/chunk/generation/utilities/noise/perlin_noise_2d.h"

namespace			game
{
	class			decoration_generator;
}

class				game::decoration_generator
{
public :

					decoration_generator(float frequency, float area);
	bool 			operator () (const vec2 &column)const;

private :

	float			area;
	perlin_noise_2d	noise;
};