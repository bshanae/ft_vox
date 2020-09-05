#pragma once

namespace						world
{
	struct						block_settings;
}

struct							world::block_settings
{
	static inline const char	light_level_min = 4;
	static inline const char 	light_level_max = 16;

	static inline const char 	default_light_level = 10;
	static inline const char	sun_light_level = 15;
};