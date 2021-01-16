#pragma once

#include "game/world/chunk/generator/noise/random_noise.h"

namespace					world
{
	class					perlin_noise;
}

class 						world::perlin_noise
{
public :

	explicit				perlin_noise
							(
								float seed = 1.f,
								float frequency = 1.f,
								float multiplier = 1.f
							) :
								seed(seed),
								frequency(frequency),
								multiplier(multiplier)
							{}

	float					generate(vec2 input) const
	{
		input *= frequency;

		const vec2			whole = floor(input);
		const vec2			fractional = fract(input);

		static const float	pi_on_2 = M_PI * 2.f;

		float				top_left_angle = random.generate_1d(whole) * pi_on_2;
		float				top_right_angle = random.generate_1d(whole + vec2(1.0f, 0.0f)) * pi_on_2;
		float				bottom_left_angle = random.generate_1d(whole + vec2(0.0f, 1.0f)) * pi_on_2;
		float				bottom_right_angle = random.generate_1d(whole + vec2(1.0f, 1.0f)) * pi_on_2;

		vec2				top_left = rotate(vec2(1.f, 0.f), top_left_angle);
		vec2				top_right = rotate(vec2(1.f, 0.f), top_right_angle);
		vec2				bottom_left = rotate(vec2(1.f, 0.f), bottom_left_angle);
		vec2				bottom_right = rotate(vec2(1.f, 0.f), bottom_right_angle);

		float				top_left_dor = dot(top_left, fractional);
		float				top_right_dot = dot(top_right, fractional - vec2(1.0, 0.0));
		float				bottom_left_dot = dot(bottom_left, fractional - vec2(0.0, 1.0));
		float				bottom_right_dot = dot(bottom_right, fractional - vec2(1.0, 1.0));

		vec2				cubic = fractional * fractional * (3.0f - 2.0f * fractional);

		float				top_mix = mix(top_left_dor, top_right_dot, cubic.x);
		float				bottom_mix = mix(bottom_left_dot, bottom_right_dot, cubic.x);
		float				final_mix = mix(top_mix, bottom_mix, cubic.y);

		return ((final_mix + 0.5f) * multiplier);
	}

private :

	float 					seed;
	float 					frequency;
	float 					multiplier;

	random_noise			random;
};