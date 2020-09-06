#pragma once

#include "world/generator/noise/random_noise.h"

namespace					world
{
	class					cellular_noise;
}

class 						world::cellular_noise
{
public :

	struct					info
	{
		vec2				final_cell;
		float				final_value;
		float				final_distance;
	};

	explicit				cellular_noise
							(
								float seed = 1.f,
								float frequency = 1.f,
								float multiplier = 1.f
							) :
								seed(seed),
								frequency(frequency),
								multiplier(multiplier)
							{}

	info					generate(vec2 input) const
	{
		input *= frequency;

		const vec2			whole = floor(input);
		const vec2			fractional = fract(input);

		info				info;

		info.final_distance = numeric_limits<float>::max();

		for (int x = -1; x <= 1; x++)
			for (int y = -1; y <= 1; y++)
			{
				vec2		test_cell = random.generate_2d(whole + vec2(x, y)) + vec2(x, y);
				float		test_distance = length(fractional - test_cell);

				if (test_distance < info.final_distance)
				{
					info.final_distance = test_distance;
					info.final_cell = test_cell;
				}
			}

		info.final_value = random.generate_1d(info.final_cell);
		return (info);
	}

private :

	float 					seed;
	float 					frequency;
	float 					multiplier;

	random_noise			random;
};