#pragma once

#include "engine/core/object/unique_object/unique_object.h"
#include "engine/rendering/main/camera/camera_settings.h"

// TODO Remove dependency
#include "game/world/chunk/block/block_alias/block_alias.h"

#include "application/common/imports/opengl.h"
#include "application/common/imports/std.h"
#include "application/common/imports/glm.h"
#include "application/common/classes/singleton.h"

namespace					player
{
	class					camera;
}

class						player::camera : public engine::unique_object<camera>
{
public :

	struct					hit
	{
		world::block_alias	block;
		world::block::face	face;
	};

							camera();
							~camera() override = default;

	vec3					get_position() const;

	mat4					get_projection_matrix() const;
	mat4					get_view_matrix() const;

	bool					did_change() const;

	vec3					get_front() const;
	vec3					get_back() const;
	vec3					get_up() const;
	vec3					get_down() const;
	vec3					get_left() const;
	vec3					get_right() const;

	void					set_position(const vec3 &value);
	void					set_did_change(bool value);

	optional<hit>			cast_ray();

	enum class				direction
	{
		left,
		right,
		forward,
		back,
		up,
		down
	};

private :

	vec3					position;
	mat4					projection_matrix;
	mat4					view_matrix;

	const vec3				up_const = vec3(0.f, 1.f, 0.f);

	vec3					front;
	vec3					up;
	vec3					right;

	float					yaw = -90.f;
	float					pitch = 0.f;

	bool 					_did_change;

	void					update() override;
	void					recalculate();

	static float			intbound(float s, float ds);
};