#pragma once

namespace						game
{
	struct						world_settings;
}

struct							game::world_settings
{
	static inline float			visibility_limit = 150.f;
	static inline float			cashing_limit = 150.f;

	static inline float			chunks_generation_time_limit = 1.f / 60.f;
};