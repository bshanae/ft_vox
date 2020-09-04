#pragma once

#include "FastNoise.h"
#include "common/glm.h"

class 							noise
{
public :

	explicit					noise
								(
									FastNoise::NoiseType type = FastNoise::Perlin,
									float frequency = 0.01f,
									float multiplier = 1.f
								) :
									multiplier(multiplier)
	{
		generator.SetNoiseType(type);
		generator.SetFrequency(frequency);
	}
								~noise() = default;

	float 						operator () (float x, float y) const
	{
		return (generate(x, y));
	}

	float 						operator () (const vec2 &value) const
	{
		return (generate(value.x, value.y));
	}

	float 						operator () (const vec3 &value) const
	{
		return (generate(value.x, value.z));
	}

private :

	float						generate(float x, float y) const
	{
		return ((generator.GetNoise(x, y) + 1.f) * multiplier);
	}

	FastNoise					generator;
	float 						multiplier;
};
