#include "height_interpolator.h"

using namespace		game;

					height_interpolator::height_interpolator(const function<int(vec2)> &height_generator) :
						height_generator(height_generator)
{}

int					height_interpolator::operator () (const vec2 &initial_position) const
{
	float			final_height = 0.f;
	float			total_weight = 0.f;

	for (int x = -8; x <= 8; x += 2)
	for (int y = -8; y <= 8; y += 2)
	{
		const auto	position_of_neighbor = (vec2)initial_position + vec2(x, y);
		const auto	height_of_neighbor = height_generator(position_of_neighbor);
		const auto	weight_of_neighbor = 1.f - 1.f / (1.f + (float)abs(x) + (float)abs(y));

		final_height += (float)height_of_neighbor * weight_of_neighbor;
		total_weight += weight_of_neighbor;
	}

	final_height /= total_weight;

	return (int)final_height;
}
