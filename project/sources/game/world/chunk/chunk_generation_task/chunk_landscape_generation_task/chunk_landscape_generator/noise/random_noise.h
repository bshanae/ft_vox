#pragma once

#include "application/common/imports/glm.h"

namespace				game
{
    class				random_noise;
}

class 					game::random_noise
{
public :

                        random_noise() = default;
                        ~random_noise() = default;
public :

    float				generate_1d(vec2 input) const
    {
        input = mod(input, vec2(10000.f));

        return ((float)fract(sin(dot(input, const_vector_1d)) * const_factor));
    }

    vec2				generate_2d(vec2 input) const
    {
        input = mod(input, vec2(10000.f));

        return fract(
                sin(vec2(dot(input, const_vector_2d1), dot(input, const_vector_2d2)))
                * const_factor);
    }

private :

    static inline float	const_factor = 43758.5453f;
    static inline vec2	const_vector_1d = vec2(12.9898f, 78.233f);
    static inline vec2	const_vector_2d1 = vec2(127.1f, 311.7f);
    static inline vec2	const_vector_2d2 = vec2(269.5f, 183.3f);
};