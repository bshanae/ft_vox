#include "camera.h"

#include "engine/main/system/window/window.h"
#include "engine/main/system/input/input.h"

#include "game/world/world/world.h"

using namespace			engine;
using namespace			game; // TODO

						camera::camera()
{
	set_layout("System");
	position = camera_settings::initial_position;
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

bool					camera::did_change()
{
	return get_instance()->_did_change;
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

void					camera::set_position(const vec3 &value)
{
	auto				instance = get_instance();

	instance->position = value;
	instance->recalculate();
}

void					camera::set_did_change(bool value)
{
	get_instance()->_did_change = value;
}

void					camera::when_updated()
{
	_did_change = input::did_mouse_move();

	yaw += input::get_mouse_offset().x * camera_settings::rotation_speed;
	pitch += input::get_mouse_offset().y * camera_settings::rotation_speed;

	if (_did_change)
		recalculate();
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
	right = normalize(cross((vec3)front, (vec3)up_const));
	up = normalize(cross((vec3)right, (vec3)front));

	view_matrix = lookAt((vec3)position, (vec3)position + (vec3)front, (vec3)up);
	projection_matrix = perspective
	(
		radians(camera_settings::fov),
		(float)window::size.x / (float)window::size.y,
		camera_settings::near_plane,
		camera_settings::far_plane
	);
}

