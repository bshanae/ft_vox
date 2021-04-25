#pragma once

#include "game/world/chunk/generation/utilities/noise/perlin_noise_2d.h"

namespace			game
{
	class			decoration_generator;
}

class				game::decoration_generator
{
public :

	explicit		decoration_generator(float frequency);
	bool 			operator () (const vec2 &column)const;

private :

	perlin_noise_2d	noise;
};