#pragma once

#include "common/aliases.h"
#include "libraries/FastNoise/FastNoise.h"

class				generator
{
public:
					generator() = default;
	virtual			~generator() = default;

	virtual float	get_noise(float x, float y) = 0;
	virtual float	get_noise(float x, float y, float z) = 0;

protected :

	FastNoise		noise;
};
/*
mapHeight[] = getheight
 3dmap for(xyz)
 {
 	y >  height = air
 	{
 		200 < getGenerator(dimod)
 		else
 			stome
 	}
 }
 */