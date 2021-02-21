#pragma once

namespace						game
{
	struct						world_settings;
}

struct							game::world_settings
{
	static inline float			fog_limit = 200.f;
	static inline float			visibility_limit = 300.f;
	static inline float			cashing_limit = 300.f;

	static inline float			chunks_generation_time_limit = 1.f / 120.f;
};