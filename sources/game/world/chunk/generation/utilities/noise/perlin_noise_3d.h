#pragma once

#include "random_noise_1d.h"

namespace					game
{
	class					perlin_noise_3d;
}

class 						game::perlin_noise_3d
{
public :

	explicit				perlin_noise_3d
							(
								float frequency = 1.f,
								float multiplier = 1.f,
								float shift = 0.f
							) :
								frequency(frequency),
								multiplier(multiplier),
								shift(shift)
							{}

    float					operator () (vec3 input) const
    {
		static const float	pi_on_2 = M_PI * 2.f;

        input *= frequency;

        const vec3			whole = floor(input);
        const vec3			fractional = fract(input);

        float				left_top_further_angle = random(whole) * pi_on_2;
        float				left_top_nearest_angle = random(whole + vec3(0.0f, 0.0f, 1.0f)) * pi_on_2;

        float				right_top_further_angle = random(whole + vec3(1.0f, 0.0f, 0.0f)) * pi_on_2;
        float				right_top_nearest_angle = random(whole + vec3(1.0f, 0.0f, 1.0f)) * pi_on_2;

        float				left_bottom_further_angle = random(whole + vec3(0.0f, 1.0f, 0.0f)) * pi_on_2;
        float				left_bottom_nearest_angle = random(whole + vec3(0.0f, 1.0f, 1.0f)) * pi_on_2;

        float				right_bottom_further_angle = random(whole + vec3(1.0f, 1.0f, 0.0f)) * pi_on_2;
        float				right_bottom_nearest_angle = random(whole + vec3(1.0f, 1.0f, 1.0f)) * pi_on_2;

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

	float 					frequency;
	float 					multiplier;
	float 					shift;

	random_noise_1d			random;
};