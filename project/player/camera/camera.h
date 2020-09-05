#pragma once

#include "common/opengl.h"
#include "common/aliases.h"
#include "common/global.h"
#include "common/property.h"
#include "engine/object/unique_object/unique_object.h"
#include "world/block/block_id/block_id.h"
#include "player/camera/camera_settings.h"

namespace								player
{
	class								camera;
}

class									player::camera : public engine::unique_object<camera>
{
public :
										camera();
										~camera() override = default;

	static inline
	property<read_write, vec3, camera>	position;

	static inline
	property<read_only, mat4, camera>	projection_matrix;
	static inline
	property<read_only, mat4, camera>	view_matrix;

	static inline
	property<read_write, bool, camera>	have_changed;

	static inline
	property<read_only, vec3, camera>	front;
	static inline
	property<read_only, vec3, camera>	back;
	static inline
	property<read_only, vec3, camera>	up;
	static inline
	property<read_only, vec3, camera>	down;
	static inline
	property<read_only, vec3, camera>	left;
	static inline
	property<read_only, vec3, camera>	right;

	struct								hit
	{
		world::block_id					block;
		world::block::face				face;
	};

	static optional<hit>				cast_ray();

	enum class							move_request
	{
		left,
		right,
		forward,
		back,
		up,
		down
	};

private :

	const vec3							up_const = vec3(0.f, 1.f, 0.f);

	float								yaw = -90.f;
	float								pitch = 0.f;

	void								update() override;

	void								recalculate();

	vec3								move_position(move_request request, float speed);
	static float						intbound(float s, float ds);
};