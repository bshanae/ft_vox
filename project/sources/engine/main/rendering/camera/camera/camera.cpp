#include "camera.h"

#include "engine/main/system/window/window.h"
#include "engine/main/system/input/input.h"
#include "engine/main/rendering/camera/camera_event/camera_position_changed_event.h"
#include "engine/main/rendering/camera/camera_event/camera_direction_changed_event.h"

using namespace			engine;

						camera::camera()
{
	set_layout("System");
	recalculate();
}

vec3					camera::get_position()
{
	return get_instance()->position;
}

mat4					camera::get_projection_matrix()
{
	return get_instance()->projection_matrix;
}

mat4					camera::get_view_matrix()
{
	return get_instance()->view_matrix;
}

vec3					camera::get_front()
{
	return get_instance()->front;
}

vec3					camera::get_back()
{
	return get_front() * -1.f;
}

vec3					camera::get_up()
{
	return get_instance()->up;
}

vec3					camera::get_down()
{
	return get_instance()->up * -1.f;
}

vec3					camera::get_left()
{
	return get_instance()->right * -1.f;
}

vec3					camera::get_right()
{
	return get_instance()->right;
}

float					camera::get_fov()
{
	return get_instance()->fov;
}

void					camera::set_position(const vec3 &value)
{
	auto				instance = get_instance();

	instance->position = value;
	instance->recalculate();

	instance->notify(camera_position_changed_event());
}

void					camera::when_updated()
{
	const float			yaw_change = input::get_mouse_offset().x * camera_settings::rotation_speed;
	const float			pitch_change = input::get_mouse_offset().y * camera_settings::rotation_speed;

	float				new_fov = fov;

	if (abs(yaw_change) > epsilon || abs(pitch_change) > epsilon)
	{
		yaw += yaw_change;
		pitch += pitch_change;

		recalculate();
		notify(camera_direction_changed_event());
	}

	if (input::is_held(input::key::command) and input::is_held(input::key::letter_f))
	{
		if (input::is_pressed_or_held(input::key::plus))
			new_fov += camera_settings::fov_delta;
		else if (input::is_pressed_or_held(input::key::minus))
			new_fov -= camera_settings::fov_delta;
	}

	new_fov = clamp(new_fov, camera_settings::minimum_fov, camera_settings::maximum_fov);
	if (new_fov != fov)
	{
		fov = new_fov;
		recalculate();
	}
}

void					camera::recalculate()
{
	vec3				local_front;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	local_front.x = cos(radians(yaw)) * cos(radians(pitch));
	local_front.y = sin(radians(pitch));
	local_front.z = sin(radians(yaw)) * cos(radians(pitch));
	front = normalize(local_front);
	right = normalize(cross(front, up_const));
	up = normalize(cross(right, front));

	view_matrix = lookAt(position, position + front, up);
	projection_matrix = perspective
	(
		radians(fov),
		(float)window::get_size().x / (float)window::get_size().y,
		camera_settings::near_plane,
		camera_settings::far_plane
	);
}