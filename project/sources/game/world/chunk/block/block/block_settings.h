#pragma once

namespace						game
{
	struct						block_settings;
}

struct							game::block_settings
{
	static constexpr float		min_light = 0.1f;

	static constexpr float		default_light = 0.95f;
	static constexpr float		sun_light = 1.f;
};