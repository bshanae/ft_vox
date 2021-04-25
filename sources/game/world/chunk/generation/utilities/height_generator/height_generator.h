#pragma once

#include "application/common/defines.h"
#include "application/common/imports/glm.h"

#include "game/world/chunk/generation/utilities/noise/perlin_noise_2d.h"

namespace					game
{
	class					height_generator;
}

class						game::height_generator
{
public :

	int 					operator () (const vec2 &column) const;
	void					add_layer(float frequency, float multiplier, float power);

private :

	vector<perlin_noise_2d>	layers;
};
