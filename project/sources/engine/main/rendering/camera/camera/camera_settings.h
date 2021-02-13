#pragma once

#include "application/common/imports/glm.h"

namespace					engine
{
	struct					camera_settings;
}

struct						engine::camera_settings
{
	static constexpr float	rotation_speed = 0.05f;

	static inline float		near_plane = 0.05f;
	static inline float		far_plane = 250.f;

	static inline float 	default_fov = 50.f;
	static inline float 	minimum_fov = 40.f;
	static inline float 	maximum_fov = 120.f;
	static inline float 	fov_delta = 2.f;

	static inline vec3		initial_position = vec3(0.f, 30.0f, 0.f); // TODO Make this dynamic
};