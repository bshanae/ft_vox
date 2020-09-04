#pragma once

#include "common/glm.h"

class 				noise
{
public :

	explicit		noise(float frequency = 0.01f, float multiplier = 1.f) :
						frequency(frequency),
						multiplier(multiplier)
					{}
					~noise() = default;

	virtual float	operator () (float x, float y) const
	{
		return (generate_final(x, y));
	}

	float 			operator () (const vec2 &value) const
	{
		return (generate_final(value.x, value.y));
	}

	float 			operator () (const vec3 &value) const
	{
		return (generate_final(value.x, value.z));
	}

protected :

	virtual float	generate(float x, float y) const = 0;

	float 			frequency;
	float 			multiplier;

private :

	float			generate_final(float x, float y) const
	{
		return (generate(frequency * x, frequency * y) * multiplier);
	}
};
