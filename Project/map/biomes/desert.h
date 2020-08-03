#pragma once
#include "map/biomes/biome.h"
class desert : public biome
{
public:
	desert()
	: biome()
	{

	}
	~desert() = default;
	static constexpr  int octaves = 9;
	static constexpr int amplitude = 80;
	static constexpr int smoothness = 335;
	static constexpr int heightOffset = -7;
	static constexpr float roughness = 0.5;
	static constexpr  float frequency = 0.5f;

};
