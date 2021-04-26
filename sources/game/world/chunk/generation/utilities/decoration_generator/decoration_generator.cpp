#include "decoration_generator.h"

#include "application/common/defines.h"

using namespace	game;

				decoration_generator::decoration_generator(float frequency, float area) :
					noise(frequency),
					area(area)
{}

bool 			decoration_generator::operator () (const vec2 &column) const
{
	return noise(column) > area;
}