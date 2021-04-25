#pragma once

#include "application/common/imports/opengl.h"
#include "application/common/imports/std.h"
#include "application/common/imports/glm.h"
#include "application/common/templates/singleton/singleton.h"

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/main/rendering/camera/direction/direction.h"
#include "engine/main/rendering/camera/camera_event/camera_event.h"
#include "engine/main/rendering/camera/camera/camera_settings.h"

namespace				engine
{
	class				camera;
}

class					engine::camera :
							public engine::object,
							public engine::unique_object_constructor<engine::camera>,
							public notifier<engine::camera_event>
{
public :
						camera();
						~camera() override = default;

	static vec3			get_position();

	static mat4			get_projection_matrix();
	static mat4			get_view_matrix();

	static vec3			get_front();
	static vec3			get_back();
	static vec3			get_up();
	static vec3			get_down();
	static vec3			get_left();
	static vec3			get_right();
	static float		get_fov();

	static void			set_position(const vec3 &value);

private :

	static const inline
	float				epsilon = 0.0001f;

	vec3				position;
	mat4				projection_matrix;
	mat4				view_matrix;

	const vec3			up_const = vec3(0.f, 1.f, 0.f);

	vec3				front;
	vec3				up;
	vec3				right;

	float				fov = camera_settings::default_fov;

	float				yaw = -90.f;
	float				pitch = 0.f;

	void				when_updated() override;
	void				recalculate();

	static float		intbound(float s, float ds);
};