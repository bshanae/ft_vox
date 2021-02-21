#pragma once

#include "application/common/imports/std.h"
#include "application/common/imports/glm.h"
#include "application/common/imports/FastNoise.h"

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

#include "game/world/chunk/chunk/generation/chunk_workspace/chunk_workspace.h"
#include "game/world/chunk/chunk/generation/generators/chunk_landscape_generator/noise/cellular_noise.h"
#include "game/world/chunk/chunk/generation/generators/chunk_landscape_generator/biome/biome_collection/biome_collection.h"

namespace			game
{
	class			chunk;

	class			chunk_landscape_generator;
}

class				game::chunk_landscape_generator : public singleton<game::chunk_landscape_generator>
{
public :
					chunk_landscape_generator();
					~chunk_landscape_generator() override = default;

	static void 	process(const shared_ptr<chunk_workspace> &workspace);

private :

	struct			column_info
	{
		const biome	&biome;
		int 		height;
	};

	cellular_noise	noise_for_biome;

	void			do_process(const shared_ptr<chunk_workspace> &workspace);
	column_info		process_column(const vec3 &position);
	const biome		&choose_biome(float noise_value);
};


