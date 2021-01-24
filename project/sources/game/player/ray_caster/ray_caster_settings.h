#pragma once

#include "game/world/chunk/block/block_alias/block_alias.h"

namespace				game
{
	class 				ray_caster_settings;
}

struct					game::ray_caster_settings
{
	static inline int	ray_cast_limit = 15;
};