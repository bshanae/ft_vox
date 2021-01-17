#pragma once

namespace						game
{
	struct 						player_settings;
}

struct							game::player_settings
{
	static inline const float	movement_speed = 0.15f;

	static inline const vec3	gravity_force = vec3(0.f, -0.007f, 0.f);
	static inline const float	movement_force = 0.15f;
	static inline const vec3	jump_force = vec3(0.f, 0.15f, 0.f);

	static inline const vec3	flight_lift = vec3(0.f, movement_speed, 0.f);
	static inline const float	speed_up = 12.f;

	static inline const vec3	aabb_size = vec3(0.3f, 1.9f, 0.3f);

	static inline const float	second_space_wait = 0.3f;
};

