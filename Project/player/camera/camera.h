#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"
#include "common/global.h"
#include "common/property.h"
#include "core/object/unique_object.h"
#include "world/block/block_id.h"
#include "player/camera/camera_settings.h"

class						camera : public unique_object<camera>
{
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

	enum class				move_request
	{
		left,
		right,
		forward,
		back,
		up,
		down
	};

	static void				move(move_request request, float speed);

private :

	const vec3				up_const = vec3(0.f, 1.f, 0.f);

	vec3					front = vec3(0.f, 0.f, -1.f);
	vec3					up = up_const;
	vec3					right = vec3(1.f, 0.f, 0.f);

	float					yaw = -90.f;
	float					pitch = 0.f;

	void					update() override;

	void					recalculate();

	void					move_non_static(move_request request, float speed);
	static float			intbound(float s, float ds);
};