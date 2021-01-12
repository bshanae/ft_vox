#pragma once

namespace				world
{
	class				random_noise;
}

class 					world::random_noise
{
public :

						random_noise() = default;
						~random_noise() = default;
public :

	float				generate_1d(vec2 input) const
	{
		input = mod(input, vec2(10000.f));

 		return ((float)fract(sin(dot(vec2(input.x, input.y), some_vector)) * 43758.5453f));
	}

	vec2				generate_2d(vec2 input) const
	{
		input = mod(input, vec2(10000.f));

		return
		(
			fract
			(
				sin
				(
					vec2
					(
						dot(vec2(input.x, input.y), vec2(127.1f, 311.7f)),
						dot(vec2(input.x, input.y), vec2(269.5f, 183.3f)))
					)
					* 43758.5453f
			)
		);
	}

private :

	static inline vec2	some_vector = vec2(12.9898f, 78.233);
};