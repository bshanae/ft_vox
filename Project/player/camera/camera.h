#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/global.h"
#include "common/property.h"
#include "application/unique_object.h"
#include "world/block/block_id.h"

struct						camera_settings
{
	static constexpr float	movement_speed = 0.15f;
	static constexpr float	rotation_speed = 0.05f;

	static inline float		near_plane = 0.01f;
	static inline float		far_plane = 100.f;
	static inline float 	fov = 30.f;

	static inline vec3		initial_position = vec3(0.f, 5.0f, 0.f);

	static inline int		ray_cast_limit = 15;
};

class						camera : public unique_object<camera>
{
	friend class			application;

	using					position_type = property<read_write, vec3, camera>;
	using					projection_matrix_type = property<read_only, mat4, camera>;
	using					view_matrix_type = property<read_only, mat4, camera>;
	using					flag_type = property<read_write, bool, camera>;

public :
							camera();
							~camera() override = default;

	static inline
	position_type			position;

	static inline
	projection_matrix_type	projection_matrix;
	static inline
	view_matrix_type		view_matrix;

	struct					hit
	{
		block_id			block;
		block::face			face;
	};

	static optional<hit>	cast_ray();

	static inline
	flag_type				have_changed;

private :

	const vec3				up_const = vec3(0.f, 1.f, 0.f);

	vec3					front = vec3(0.f, 0.f, -1.f);
	vec3					up = up_const;
	vec3					right = vec3(1.f, 0.f, 0.f);

	float					yaw = -90.f;
	float					pitch = 0.f;

	void					update() override;

	void					recalculate();

	static float			intbound(float s, float ds);
};