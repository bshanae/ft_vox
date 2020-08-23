#pragma once

struct							player_settings
{
	static inline const float	movement_speed = 0.2f;
	static inline const vec3	aabb_size = vec3(0.3f, 1.9f, 0.3f);

	static inline const vec3	gravity_force = vec3(0.f, -0.03f, 0.f);
	static inline const vec3	jump_force = vec3(0.f, 0.5f, 0.f);
};

