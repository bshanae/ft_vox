#pragma once
#include "generation/noise_generator.h"

class biome
{
public:

	static constexpr  float frequency = 0.5f;

	biome() = default;
	~biome() = default;

	int get_height(int x, int z)
	{
		return generator.getHeight(x,z,0,0);
	}

private:
	static constexpr  int octaves = 7;
	static constexpr int amplitude = 70;
	static constexpr int smoothness = 235;
	static constexpr int heightOffset = -5;
	static constexpr float roughness = 0.93;
	noise_generator generator = noise_generator(1337);

};
