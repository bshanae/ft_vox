#pragma once

#include "world/chunk/chunk_settings.h"
#include "world/world/world_settings.h"

namespace					player
{
	struct					camera_settings;
}

struct						player::camera_settings
{
	static constexpr float	rotation_speed = 0.05f;

	static inline float		near_plane = 0.05f;
	static inline float		far_plane = world::world_settings::visibility_limit + 100.f;
	static inline float 	fov = 50.f;

	static inline vec3		initial_position = vec3(0.f, 5.0f, 0.f);

	static inline int		ray_cast_limit = 15;
};