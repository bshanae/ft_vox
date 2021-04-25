#pragma once

#include "game/world/block/block_ptr/block_ptr.h"

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
		block_ptr			block;
		block_face			face;
	};

	static optional<hit>	cast_ray();
};


