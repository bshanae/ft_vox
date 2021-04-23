#pragma once

#include "game/world/chunk/chunk_generation_task/chunk_landscape_generation_task/chunk_landscape_generator/noise/random_noise.h"

namespace					game
{
	class					perlin_noise;
}

class 						game::perlin_noise
{
public :

	explicit				perlin_noise
							(
								int seed = 0,
								float frequency = 1.f,
								float multiplier = 1.f,
								float shift = 0.f
							) :
								seed(seed),
								frequency(frequency),
								multiplier(multiplier),
								shift(shift)
							{}

	float					generate(vec2 input) const
	{
        input *= frequency;

		const vec2			whole = floor(input);
		const vec2			fractional = fract(input);

		static const float	pi_on_2 = M_PI * 2.f;

		float				top_left_angle = random.generate_1d(whole, seed) * pi_on_2;
		float				top_right_angle = random.generate_1d(whole + vec2(1.0f, 0.0f), seed) * pi_on_2;
		float				bottom_left_angle = random.generate_1d(whole + vec2(0.0f, 1.0f), seed) * pi_on_2;
		float				bottom_right_angle = random.generate_1d(whole + vec2(1.0f, 1.0f), seed) * pi_on_2;

		vec2				top_left = rotate(vec2(1.f, 0.f), top_left_angle);
		vec2				top_right = rotate(vec2(1.f, 0.f), top_right_angle);
		vec2				bottom_left = rotate(vec2(1.f, 0.f), bottom_left_angle);
		vec2				bottom_right = rotate(vec2(1.f, 0.f), bottom_right_angle);

		float				top_left_dot = dot(top_left, fractional);
		float				top_right_dot = dot(top_right, fractional - vec2(1.0, 0.0));
		float				bottom_left_dot = dot(bottom_left, fractional - vec2(0.0, 1.0));
		float				bottom_right_dot = dot(bottom_right, fractional - vec2(1.0, 1.0));

		vec2				cubic = fractional * fractional * (3.0f - 2.0f * fractional);

		float				top_mix = mix(top_left_dot, top_right_dot, cubic.x);
		float				bottom_mix = mix(bottom_left_dot, bottom_right_dot, cubic.x);
		float				final_mix = mix(top_mix, bottom_mix, cubic.y);

		return (final_mix + 0.5f) * multiplier + shift;
	}

    float					generate_3d(vec3 input) const
    {
		static const float	pi_on_2 = M_PI * 2.f;

        input *= frequency;

        const vec3			whole = floor(input);
        const vec3			fractional = fract(input);

        float				left_top_further_angle = random.generate_1d(whole, seed) * pi_on_2;
        float				left_top_nearest_angle = random.generate_1d(whole + vec3(0.0f, 0.0f, 1.0f), seed) * pi_on_2;

        float				right_top_further_angle = random.generate_1d(whole + vec3(1.0f, 0.0f, 0.0f), seed) * pi_on_2;
        float				right_top_nearest_angle = random.generate_1d(whole + vec3(1.0f, 0.0f, 1.0f), seed) * pi_on_2;

        float				left_bottom_further_angle = random.generate_1d(whole + vec3(0.0f, 1.0f, 0.0f), seed) * pi_on_2;
        float				left_bottom_nearest_angle = random.generate_1d(whole + vec3(0.0f, 1.0f, 1.0f), seed) * pi_on_2;

        float				right_bottom_further_angle = random.generate_1d(whole + vec3(1.0f, 1.0f, 0.0f), seed) * pi_on_2;
        float				right_bottom_nearest_angle = random.generate_1d(whole + vec3(1.0f, 1.0f, 1.0f), seed) * pi_on_2;


        vec3                normal = normalize(vec3(1, 1, 1));

        vec3				left_top_further = rotate(vec3(1.f, 0.f, 0.f), left_top_further_angle, normal);
        vec3				left_top_nearest = rotate(vec3(1.f, 0.f, 0.f), left_top_nearest_angle, normal);

        vec3				right_top_further = rotate(vec3(1.f, 0.f, 0.f), right_top_further_angle, normal);
        vec3				right_top_nearest = rotate(vec3(1.f, 0.f, 0.f), right_top_nearest_angle, normal);

        vec3				left_bottom_further = rotate(vec3(1.f, 0.f, 0.f), left_bottom_further_angle, normal);
        vec3				left_bottom_nearest = rotate(vec3(1.f, 0.f, 0.f), left_bottom_nearest_angle, normal);

        vec3				right_bottom_further = rotate(vec3(1.f, 0.f, 0.f), right_bottom_further_angle, normal);
        vec3				right_bottom_nearest = rotate(vec3(1.f, 0.f, 0.f), right_bottom_nearest_angle, normal);

        float				left_top_further_dot = dot(left_top_further, fractional);
        float				left_top_nearest_dot = dot(left_top_nearest, fractional - vec3(0.f, 0.f, 1.f));

        float				right_top_further_dot = dot(right_top_further, fractional - vec3(1.f, 0.f, 0.f));
        float				right_top_nearest_dot = dot(right_top_nearest, fractional - vec3(1.f, 0.f, 1.f));

        float				left_bottom_further_dot = dot(left_bottom_further, fractional - vec3(0.f, 1.f, 0.f));
        float				left_bottom_nearest_dot = dot(left_bottom_nearest, fractional - vec3(0.f, 1.f, 1.f));

        float				right_bottom_further_dot = dot(right_bottom_further, fractional - vec3(1.f, 1.f, 0.f));
        float				right_bottom_nearest_dot = dot(right_bottom_nearest, fractional - vec3(1.f, 1.f, 1.f));

        vec3				cubic = fractional * fractional * (3.0f - 2.0f * fractional);

        float				top_further_mix = mix(left_top_further_dot, right_top_further_dot, cubic.x);
        float				top_nearest_mix = mix(left_top_nearest_dot, right_top_nearest_dot, cubic.x);
        float				top_mix = mix(top_further_mix, top_nearest_mix, cubic.z);

        float				bottom_further_mix = mix(left_bottom_further_dot, right_bottom_further_dot, cubic.x);
        float				bottom_nearest_mix = mix(left_bottom_nearest_dot, right_bottom_nearest_dot, cubic.x);
        float				bottom_mix = mix(bottom_further_mix, bottom_nearest_mix, cubic.z);

        float				final_mix = mix(top_mix, bottom_mix, cubic.y);

        return final_mix + 0.5f;
    }

private :

	int 					seed;
	float 					frequency;
	float 					multiplier;
	float 					shift;

	random_noise			random;
};