#pragma once
#include "map/chunk_generator.h"
#include "map/biomes/biome.h"
#include "map/biomes/plain.h"
#include "map/biomes/desert.h"
#include "libraries/FastNoise/FastNoise.h"
#include "generation/noise_generator.h"
#include "map/chunk.h"
#include <memory>
#include <cmath>

class generator :  public global <generator>, public chunk_generator

{

public:
	generator() = default;
	~generator() override = default;

	void                  initializer(std::shared_ptr<generator>) override
	{
		chunk_generator::child = static_pointer_cast<chunk_generator>(instance());
		//perlin.SetSeed(1230);

		biomes[0] = biome();
		biomes[1] = desert();
//		perlin.SetNoiseType(FastNoise::Perlin);
//		//perlin.SetNoiseType(FastNoise::FBM);
////	perlin.SetFractalType(FastNoise::FBM);
//	perlin.SetSeed(1256);
////		perlin.SetFractalOctaves(8);
////////		perlin.SetFractalLacunarity(2.0f);
////   		perlin.SetFractalGain(0.5f);
//
//		perlin.SetFrequency(0.56f);
//		perlinB.reseed(7657);
	}

	int getBiome(int x, int z)
	{
		float 	height_sum 			= 0.f;
		int		count				= 0;
		float 	strongest_weight 	= 0.f;
		int		strongest_key		= 0;
		for(int i = 0; i < biomes.size(); i++)
		{
			noise.m_noiseParameters.roughness =  biomes[i].frequency;
			float weight = map(-1, 1, 0, 1, noise.getNoise(x,z)); // map 0 1
			cout << weight << endl;
			if (weight > strongest_weight)
			{
				strongest_weight = weight;
				strongest_key = i;
			}
			float height = biomes[i].get_height(x,z) * weight;
			if (height > 0)
			{
				height_sum += height;
				count++;
			}
		}
		height_sum /= count;
		return height_sum;
	}

	[[nodiscard]]
	block get_block_implementation(const vec3 &position) override
	{
		//int temp = getBiome(position.x,position.z);
		//int temp = map(0, 100, 0, 2,noise.getHeight(position.x, position.z, 0,0));

		int temp = noise.getHeight(position.x, position.z, 0,0);

		//float temp = map(-1, 1, 0, chunk_settings::size[1],noise.getNoise(position.x, position.z));
		cout << temp << endl;
		if (temp >= position.y)
			return block (block::type::dirt_with_grass);
		else
			return block (block::type::dirt_with_grass);
	}


#warning  dummy... block from generation... but why?
	 shared_ptr<chunk>	generate_implementation(const vec3 &position)
	{
		return make_shared<chunk>(chunk(vec3(0,0,0)));
	}

	int GenerateHeight(float x, float z)
	{
		float smooth = 0.01f;
		int maxHeight = 8;
		float persistence = 0.5f;
		int octaves = 4;
		float height = map( 0, 1, 0,maxHeight,fbm(x*smooth,z*smooth,octaves,persistence));
		return (int) height;
	}

	float get_noise(vec3  position, float sm = 0.5f, int octaves = 3)
	{
		return 	(fbm3D((float)position.x, (float)position.y, (float)position.z, sm, octaves));
	}

	float fbm(float x, float z, int oct = 5, float pers = 0.5f)
	{
		float total = 0;
		float frequency = 5001;
		float amplitude = 100;
		float maxValue = 0;
		float offset = 32000.f;
		for(int i = 0; i < oct ; i++)
		{
			total += map( -1, 1, 0, 1,
						  perlin.GetNoise((x +offset) * frequency, (z + offset) * frequency)) * amplitude;

			maxValue += amplitude;

			amplitude *= pers;
			frequency *= 2;
		}

		return total/maxValue;
	}
	float fbm3D(float x, float y, float z, float sm, int oct = 5)
	{
		float XY = fbm(x*sm,y*sm,oct,0.5f);
		float YZ = fbm(y*sm,z*sm,oct,0.5f);
		float XZ = fbm(x*sm,z*sm,oct,0.5f);

		float YX = fbm(y*sm,x*sm,oct,0.5f);
		float ZY = fbm(z*sm,y*sm,oct,0.5f);
		float ZX = fbm(z*sm,x*sm,oct,0.5f);

		return (XY+YZ+XZ+YX+ZY+ZX)/6.0f;
	}


private:

	FastNoise perlin;
	std::map<int, biome> biomes;
	noise_generator noise = noise_generator(1337);
	void noise_test()
	{
		FastNoise fn;
		fn.SetNoiseType(FastNoise::PerlinFractal);
		fn.SetFractalType(FastNoise::FBM);
		fn.SetFractalOctaves(3);
		fn.SetFractalLacunarity(2.0f);
		fn.SetFractalGain(0.5f);
		fn.SetFrequency(0.02f);
		fn.SetSeed(1312232);
		float noiseValue;
		for (int sy = 0; sy < 512; ++sy)
		{
			for (int sx = 0; sx < 512; ++sx)
			{
				//cout <<  fn.GetNoise((float)sx, (float)sy ) << endl;
				//cout << map(0, 256, 0, 1, fbm(sx, sy)) << endl;
//				cout << remap(-1, 1, 0, 10, fn.GetNoise((float)sx, (float)sy )) << endl;
				cout << map(-1, 1, 0, 10, fbm((float)sx, (float)sy)) << endl;
				cout << map(-1, 1, 0, 10, fbm((float)sx, (float)sy)) << endl;

			}
		}
	}

//	static float map(float origmin, float origmax, float newmin, float newmax,  float value)
//	{
//		return glm::mix(newmin, newmax, glm::smoothstep(origmin, origmax, value));
//	}


//	static float lerp(float min, float max, float value)
//	{
//		return min + value * (max - min);
//	}

	static float lerp(float a, float b, float t)
	{
		return (1.0f - t) * a + b * t;
	}
	static float inlerp(float a, float b, float v)
	{
		return (v - a) / (b - a);
	}
//	static float map( float imin, float imax, float omin, float omax, float v)
//	{
//		return lerp(omin, omax, inlerp(imin, imax, v));
//	}
	float map( float min1, float max1, float min2, float max2, float val) {
		float unitratio = (val - min1) / (max1 - min1);
		return (unitratio * (max2 - min2)) + min2;
	}
//	float map(float in_min, float in_max, float out_min, float out_max, float x)
//	{
//		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//	}
};
