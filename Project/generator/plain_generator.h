#pragma once

#include "generator/generator.h"

class				plain_generator : public generator
{
public:
					plain_generator() = default;
					~plain_generator() override = default;

	float			get_noise(float x, float y) override
	{
		return (noise.GetNoise(x, y));
	}

	float			get_noise(float x, float y, float z) override
	{
	  return (noise.GetNoise(x, y, z));
	}

	void			print()
	{

	}
};