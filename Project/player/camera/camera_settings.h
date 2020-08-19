#pragma once

struct						camera_settings
{
	static constexpr float	rotation_speed = 0.05f;

	static inline float		near_plane = 0.01f;
	static inline float		far_plane = 100.f;
	static inline float 	fov = 30.f;

	static inline vec3		initial_position = vec3(0.f, 5.0f, 0.f);

	static inline int		ray_cast_limit = 15;
};