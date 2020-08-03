#pragma once

struct noise_parameters {
	int octaves;
	int amplitude;
	int smoothness;
	int heightOffset;

	double roughness;
};

class noise_generator {
public:
	noise_generator(int seed);

	double getHeight(int x, int z, int chunkX, int chunkZ) const noexcept;

	void setParameters(const noise_parameters &params) noexcept;
	double getNoise(double x, double z) const noexcept;
	noise_parameters m_noiseParameters;

private:
	double getNoise(int n) const noexcept;

	double lerp(double a, double b, double z) const noexcept;

	double noise(double x, double z) const noexcept;


	int m_seed;
};