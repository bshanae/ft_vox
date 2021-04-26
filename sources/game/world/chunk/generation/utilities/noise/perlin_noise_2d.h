#pragma once

#include "application/common/imports/std.h"

#include "random_noise_1d.h"

namespace					game
{
	class					perlin_noise_2d;
}

class 						game::perlin_noise_2d
{
public :

	explicit				perlin_noise_2d
							(
								float frequency = 1.f,
								float multiplier = 1.f,
								float power = 1.f
							) :
								frequency(frequency),
								multiplier(multiplier),
								power(power)
							{}


	static inline shared_mutex mutex;
	static void write(string string)
	{
		lock_guard lock(mutex);
		cout << string << endl;
	}

	float					operator () (vec2 input) const
	{
        input *= frequency;

		const vec2			whole = floor(input);
		const vec2			fractional = fract(input);

		static const float	pi_on_2 = M_PI * 2.f;

		const float			top_left_angle = random(whole) * pi_on_2;
		const float			top_right_angle = random(whole + vec2(1.0f, 0.0f)) * pi_on_2;
		const float			bottom_left_angle = random(whole + vec2(0.0f, 1.0f)) * pi_on_2;
		const float			bottom_right_angle = random(whole + vec2(1.0f, 1.0f)) * pi_on_2;

		const vec2			top_left = rotate(vec2(1.f, 0.f), top_left_angle);
		const vec2			top_right = rotate(vec2(1.f, 0.f), top_right_angle);
		const vec2			bottom_left = rotate(vec2(1.f, 0.f), bottom_left_angle);
		const vec2			bottom_right = rotate(vec2(1.f, 0.f), bottom_right_angle);

		const float			top_left_dot = dot(top_left, fractional);
		const float			top_right_dot = dot(top_right, fractional - vec2(1.0, 0.0));
		const float			bottom_left_dot = dot(bottom_left, fractional - vec2(0.0, 1.0));
		const float			bottom_right_dot = dot(bottom_right, fractional - vec2(1.0, 1.0));

		const vec2			cubic = fractional * fractional * (3.0f - 2.0f * fractional);

		const float			top_mix = mix(top_left_dot, top_right_dot, cubic.x);
		const float			bottom_mix = mix(bottom_left_dot, bottom_right_dot, cubic.x);
		const float			final_mix = mix(top_mix, bottom_mix, cubic.y);

		const float 		raw_value = clamp(final_mix + 0.5f, 0.f, 1.f);
		const float 		final_value = pow(raw_value, power) * multiplier;

		return final_value;
	}

private :

	float 					frequency;
	float 					multiplier;
	float 					power;

	random_noise_1d			random;
};