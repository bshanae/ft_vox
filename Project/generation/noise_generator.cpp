//
// Created by Oles Gedz on 03/08/2020.
//

#include "noise_generator.h"

#include <cmath>
#include "map/chunk.h"
noise_generator::noise_generator(int seed)
		: m_seed(seed)
{
	m_noiseParameters.octaves = 7;
	m_noiseParameters.amplitude = 70;
	m_noiseParameters.smoothness = 235;
	m_noiseParameters.heightOffset = -5;
	m_noiseParameters.roughness = 0.93;
}

void noise_generator::setParameters(const noise_parameters &params) noexcept
{
	m_noiseParameters = params;
}

double noise_generator::getNoise(int n) const noexcept
{
	n += m_seed;
	n = (n << 13) ^ n;
	auto newN = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;

	return 1.0 - ((double)newN / 1073741824.0);
}

double noise_generator::getNoise(double x, double z) const noexcept
{
	return getNoise(x + z * 57.0);
}

double noise_generator::lerp(double a, double b, double z) const noexcept
{
	double mu2 = (1 - std::cos(z * 3.14)) / 2;
	return (a * (1 - mu2) + b * mu2);
}

double noise_generator::noise(double x, double z) const noexcept
{
	auto floorX = (double)((
			int)x);
	auto floorZ = (double)((int)z);

	auto s = 0.0, t = 0.0, u = 0.0,
			v = 0.0; // Integer declaration

	s = getNoise(floorX, floorZ);
	t = getNoise(floorX + 1, floorZ);
	u = getNoise(
			floorX,
			floorZ + 1);
	v = getNoise(floorX + 1, floorZ + 1);

	auto rec1 = lerp(s, t, x - floorX); // Interpolate between the values.
	auto rec2 = lerp(
			u, v,
			x - floorX); // Here we use x-floorX, to get 1st dimension. Don't mind
	// the x-floorX thingie, it's part of the cosine formula.
	auto rec3 =
			lerp(rec1, rec2,
				 z - floorZ); // Here we use y-floorZ, to get the 2nd dimension.
	return rec3;
}

double noise_generator::getHeight(int x, int z, int chunkX, int chunkZ) const
noexcept
{
	auto newX = (x + (chunkX * chunk_settings::size[0]));
	auto newZ = (z + (chunkZ * chunk_settings::size[2]));


	auto totalValue = 0.0;

	for (auto a = 0; a < m_noiseParameters.octaves - 1;
		 a++) // This loops through the octaves.
	{
		auto frequency = pow(
				2.0,
				a); // This increases the frequency with every loop of the octave.
		auto amplitude = pow(
				m_noiseParameters.roughness,
				a); // This decreases the amplitude with every loop of the octave.
		totalValue +=
				noise(((double)newX) * frequency / m_noiseParameters.smoothness,
					  ((double)newZ) * frequency / m_noiseParameters.smoothness) *
				amplitude;
	}

	auto val = (((totalValue / 2.1) + 1.2) * m_noiseParameters.amplitude) +
			   m_noiseParameters.heightOffset;

	return val > 0 ? val : 1;
}