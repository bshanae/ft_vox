#pragma once
#include "map/biomes/biome.h"
class desert : public biome
{
public:
	desert()
	: biome()
	{
		frequency = 0.13f;
		octaves = 3;
	}
	~desert() = default;

};
