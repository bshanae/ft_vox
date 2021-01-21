#pragma once

#include "game/world/chunk/block/block_alias/block_alias.h"

namespace					game
{
	class 					ray_caster;
}

class						game::ray_caster
{
public :

	struct					hit
	{
		block_alias			block;
		block::face			face;
	};

	static optional<hit>	cast_ray();
};


