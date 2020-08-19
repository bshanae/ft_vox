#pragma once

struct							world_settings
{
	static inline float			visibility_limit = 60.f;
	static inline float			cashing_limit = 80.f;

	static inline float			chunk_generation_time_limit = 1.f / 120.f;
};