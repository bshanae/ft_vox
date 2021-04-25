#pragma once

namespace						game
{
	struct 						player_settings;
}

struct							game::player_settings
{
	static constexpr float		movement_speed = 10.f;

	static constexpr vec3		flight_lift = vec3(0.f, movement_speed, 0.f);
	static constexpr float		speed_up = 3.f;

	static constexpr vec3		aabb_size = vec3(0.3f, 1.5f, 0.3f);
};

