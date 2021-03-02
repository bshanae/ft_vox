#pragma once

namespace						game
{
	struct						block_settings;
}

struct							game::block_settings
{
	static constexpr float		min_light_level = 0.1f;
	static constexpr float		max_light_level = 1.0f;
	static constexpr float		default_light_level = 0.9f;

	static constexpr float		sun_light_level = 1.f;
};