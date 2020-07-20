#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/global.h"

class						camera : public global<camera>
{
	friend class			application;

public :
							camera();
							~camera() override = default;

	static inline float		near_plane = 0.f;
	static inline float		far_plane = 1000.f;
	static inline float 	fov = 30.f;

	[[nodiscard]]
	static mat4				get_projection_matrix()
	{
		return(instance()->projection_matrix);
	}

	[[nodiscard]]
	static mat4				get_view_matrix()
	{
		return (instance()->view_matrix);
	}

	vec3					position = vec3(0.f, 0.0f, 1.6f);

	float					yaw = -90.f;
	float					pitch = 0.f;

private :

	const vec3				up_const = vec3(0.f, 1.f, 0.f);

	vec3					front = vec3(0.f, 0.f, -1.f);
	vec3					up = up_const;
	vec3					right = vec3(1.f, 0.f, 0.f);

	mat4					projection_matrix = mat4(0.f);
	mat4					view_matrix = mat4(0.f);

	static constexpr float	sensitivity = 0.3f;

	void					update();

	void					recalculate();
};