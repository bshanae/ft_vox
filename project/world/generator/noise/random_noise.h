#pragma once

#include "world/generator/noise/noise.h"

class 					random_noise : public noise
{
public :

	explicit			random_noise(float frequency = 0.01f, float multiplier = 1.f) :
							noise(frequency, multiplier)
						{}
private :

	static inline vec2	some_vector = vec2(12.9898f, 78.233);

	float				generate(float x, float y) const override
	{
		return ((float)fract(sin(dot(vec2(x, y), some_vector)) * 43758.5453));
	}
};