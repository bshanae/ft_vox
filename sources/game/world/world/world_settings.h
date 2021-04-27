#pragma once

namespace							game
{
	struct							world_settings;
}

struct								game::world_settings
{
    static inline array<float, 3>	fog_limit = { 200.f };
    static inline array<float, 3>	visibility_limit = { 350.f };
    static inline array<float, 3>	cashing_limit = { 350.f };

	static inline int 				current_visibility_option = 0;
	static inline int 				max_visibility_option = 0;

	static inline float				chunks_generation_time_limit = 1.f / 120.f;
};