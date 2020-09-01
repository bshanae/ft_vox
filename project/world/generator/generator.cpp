#include "generator.h"

#include "world/chunk/chunk.h"

						generator::generator()
{
	object::layout = "System";
	object::should_be_updated = false;
	object::should_be_rendered = false;

	noise.SetNoiseType(FastNoise::Simplex);
}

shared_ptr<chunk>		generator::generate(const vec3 &position)
{
	static const int	water_level = 20;

	auto 				instance = generator::instance();

	shared_ptr<chunk>	chunk;
	chunk::index		index;

	chunk = make_shared<::chunk>(position);
	for (index.x = 0; index.x < chunk_settings::size[0]; index.x++)
		for (index.z = 0; index.z < chunk_settings::size[2]; index.z++)
		{
			const vec3	position_with_index = vec3(position.x + index.x, 0, position.z + index.z);
			const int	height_level = instance->height_level(position_with_index);

			for (index.y = 0; index.y < max(water_level, height_level); index.y++)
				if (index.y <= height_level)
					chunk->at(index).type = block::type::dirt;
				else if (index.y <= water_level)
					chunk->at(index).type = block::type::water;
		}

	return (chunk);
}

int 					generator::height_level(const vec3 &position)
{
	float				value;

	value = noise.GetNoise((int)position.x, (int)position.z);
	value = (value + 1.f) * 30.f;

	return ((int)floor(value));
}