#pragma once

#include "world/generator/noise/random_noise.h"

namespace					world
{
	class					cellular_noise;
}

class 						world::cellular_noise
{
public :

	struct					cell
	{
		vec2				position = vec2(0.f);
		float				noise_value = 0.f;
		float				distance = 0.f;
	};

	struct					result
	{
		cell				nearest;
		cell				furthest;

		cell				central;

		cell				left;
		cell				right;
		cell				top;
		cell				bottom;

		cell				top_left;
		cell				top_right;

		cell				bottom_left;
		cell				bottom_right;
	};

	explicit				cellular_noise(float frequency = 1.f) : frequency(frequency) {}

	result					generate(vec2 input) const
	{
		input *= frequency;

		const vec2			floor = glm::floor(input);
		result				result;

		result.nearest.distance = numeric_limits<float>::max();
		result.furthest.distance = numeric_limits<float>::min();

		setup_cell(result.central, floor + vec2(0.f, 0.f));
		setup_cell(result.left, floor + vec2(-1.f, 0.f));
		setup_cell(result.right, floor + vec2(+1.f, 0.f));
		setup_cell(result.top, floor + vec2(0.f, +1.f));
		setup_cell(result.bottom, floor + vec2(0.f, -1.f));
		setup_cell(result.top_left, floor + vec2(-1.f, +1.f));
		setup_cell(result.top_right, floor + vec2(+1.f, +1.f));
		setup_cell(result.bottom_left, floor + vec2(-1.f, -1.f));
		setup_cell(result.bottom_right, floor + vec2(+1.f, -1.f));

		calculate_distance(result.central, input);
		calculate_distance(result.left, input);
		calculate_distance(result.right, input);
		calculate_distance(result.top, input);
		calculate_distance(result.bottom, input);
		calculate_distance(result.top_left, input);
		calculate_distance(result.top_right, input);
		calculate_distance(result.bottom_left, input);
		calculate_distance(result.bottom_right, input);

		process_minimum(result.nearest, result.central);
		process_minimum(result.nearest, result.left);
		process_minimum(result.nearest, result.right);
		process_minimum(result.nearest, result.top);
		process_minimum(result.nearest, result.bottom);
		process_minimum(result.nearest, result.top_left);
		process_minimum(result.nearest, result.top_right);
		process_minimum(result.nearest, result.bottom_left);
		process_minimum(result.nearest, result.bottom_right);

		process_maximum(result.furthest, result.central);
		process_maximum(result.furthest, result.left);
		process_maximum(result.furthest, result.right);
		process_maximum(result.furthest, result.top);
		process_maximum(result.furthest, result.bottom);
		process_maximum(result.furthest, result.top_left);
		process_maximum(result.furthest, result.top_right);
		process_maximum(result.furthest, result.bottom_left);
		process_maximum(result.furthest, result.bottom_right);

		return (result);
	}

	result					generate(const vec3 &input) const
	{
		return (generate({input.x, input.z}));
	}

private :

	float 					frequency;

	random_noise			random;

	void					setup_cell(cell &cell, const vec2 &position) const
	{
		cell.position = position + random.generate_2d(position);
		cell.noise_value = random.generate_1d(cell.position);
	}

	void 					calculate_distance(cell &cell, const vec2 &point) const
	{
		cell.distance = length(point - cell.position);
	}

	static void 			process_minimum(cell &minimum, cell &test)
	{
		if (test.distance < minimum.distance)
			minimum = test;
	}

	static void 			process_maximum(cell &maximum, cell &test)
	{
		if (test.distance > maximum.distance)
			maximum = test;
	}
};