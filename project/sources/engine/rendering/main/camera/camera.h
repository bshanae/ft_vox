#pragma once

#include "engine/core/object/object/object.h"
#include "engine/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/rendering/main/camera/camera_settings.h"

// TODO Remove dependency
#include "game/world/chunk/block/block_alias/block_alias.h"

#include "application/common/imports/opengl.h"
#include "application/common/imports/std.h"
#include "application/common/imports/glm.h"
#include "application/common/templates/singleton/singleton.h"

namespace					engine
{
	class					camera;
}

class						engine::camera :
								public engine::object,
								public engine::unique_object_constructor<engine::camera>
{
public :

	struct					hit
	{
		game::block_alias	block;
		game::block::face	face;
	};

							camera();
							~camera() override = default;

	static vec3				get_position();

	static mat4				get_projection_matrix();
	static mat4				get_view_matrix();

	static bool				did_change();

	static vec3				get_front();
	static vec3				get_back();
	static vec3				get_up();
	static vec3				get_down();
	static vec3				get_left();
	static vec3				get_right();

	static void				set_position(const vec3 &value);
	static void				set_did_change(bool value);

	static optional<hit>	cast_ray();

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

	void					when_updated() override;
	void					recalculate();

	static float			intbound(float s, float ds);
};