#pragma once

#include "game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generator/noise/random_noise.h"

namespace					game
{
	class					cellular_noise;
}

class 						game::cellular_noise
{
public :

	struct					cell
	{
		vec2				position = vec2(0.f);
		float				distance = 0.f;
	};

    explicit				cellular_noise(int seed = 0, float frequency = 1.f) : frequency(frequency), seed(seed) {}

	cell					generate(vec2 input) const
	{
		input *= frequency;

		const vec2			floor = glm::floor(input);

		cell                nearest;
		cell                current;

		nearest.distance = numeric_limits<float>::max();

        for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++)
        {
            position_determination(current, floor + vec2(x, y));
            calculate_distance(current, input);

            if (nearest.distance > current.distance)
            {
                nearest.position = current.position;
                nearest.distance = current.distance;
            }
        }

		return (nearest);
	}

	cell					generate(const vec3 &input) const
	{
		return (generate({input.x, input.z}));
	}

private :

	float 					frequency;
	int 					seed;

	random_noise			random;

	void					position_determination(cell &cell, const vec2 &position) const
	{
		cell.position = position + random.generate_2d(position);
	}

	void 					calculate_distance(cell &cell, const vec2 &point) const
	{
		cell.distance = length(point - cell.position);
	}
};