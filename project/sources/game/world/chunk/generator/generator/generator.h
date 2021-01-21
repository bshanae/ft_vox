#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

#include "game/world/chunk/generator/biome/biome_collection/biome_collection.h"

#include "application/common/imports/std.h"
#include "application/common/imports/glm.h"
#include "FastNoiseLite.h"

namespace			game
{
	class			chunk;

	class			generator;
}

class				game::generator :
						public engine::object,
						public engine::unique_object_constructor<generator>
{
public :
					generator();
					~generator() override = default;

	static void		generate(const shared_ptr<chunk> &chunk);

private :

	struct
	{
		vec3		position;

		biome		biome;
		int			height;
	}				workspace;

	cellular_noise	noise_for_biome;

	void			process_column(const vec3 &position);

	const biome		&choose_biome(float noise_value);
};


