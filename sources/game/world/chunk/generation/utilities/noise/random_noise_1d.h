#pragma once

#include "application/common/imports/glm.h"

namespace				game
{
    class				random_noise_1d;
}

class 					game::random_noise_1d
{
public :

                        random_noise_1d(int seed) : seed(seed) {}
                        ~random_noise_1d() = default;

    float				operator () (vec2 input) const
    {
        input = mod(input, vec2(10000.f));

        return ((float)fract(sin(dot(input, const_vector_1d_v2)) * const_factor));
    }

private :

	const int 			seed;

    static inline float	const_factor = 43758.5453f;
    static inline vec2	const_vector_1d_v2 = vec2(12.9898f, 78.233f);
};