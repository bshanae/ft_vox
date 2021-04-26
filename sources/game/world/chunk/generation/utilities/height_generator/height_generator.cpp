#include "height_generator.h"

#include "game/world/chunk/chunk/chunk_settings.h"

using namespace		game;

int 				height_generator::operator () (const vec2 &column) const
{
#if FT_VOX_MULTILAYER_HEIGHT_NOISE
	float			height = 0;

	for (const auto &layer : layers)
		height += layer(column);

	return chunk_settings::zero_height + (int)height;
#else
	return chunk_settings::zero_height + (int)layers[0](column);
#endif
}

void				height_generator::add_layer(float frequency, float multiplier, float power)
{
	layers.emplace_back(frequency, multiplier, power);
}