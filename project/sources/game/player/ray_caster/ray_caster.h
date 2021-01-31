#pragma once

#include "game/world/chunk/block/block_alias/block_alias.h"

namespace					game
{
	enum class 				block_face;
	class 					ray_caster;
}

class						game::ray_caster
{
public :

	struct					hit
	{
		block_alias			block;
		block_face			face;
	};

	static optional<hit>	cast_ray();
};


