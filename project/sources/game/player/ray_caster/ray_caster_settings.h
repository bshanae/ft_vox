#pragma once

#include "game/world/block/block_ptr/block_ptr.h"

namespace				game
{
	class 				ray_caster_settings;
}

struct					game::ray_caster_settings
{
	static inline int	ray_cast_limit = 15;
};