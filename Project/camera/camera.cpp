#include "camera.h"

#include "common/debug.h"
#include "application/window.h"
#include "application/input.h"

					camera::camera()
{
	position.setter = [this](const vec3 &value)
	{
		position.value = value;
		recalculate();
	};

	position = camera_settings::initial_position;
}

void				camera::update()
{
//					Axis X
	if (input::is_pressed_or_held(GLFW_KEY_A))
		position = (vec3)position - camera_settings::movement_speed * right;
	else if (input::is_pressed_or_held(GLFW_KEY_D))
		position = (vec3)position + camera_settings::movement_speed * right;

//					Axis y
	if (input::is_pressed_or_held(GLFW_KEY_Q))
		position = (vec3)position - camera_settings::movement_speed * up;
	else if (input::is_pressed_or_held(GLFW_KEY_E))
		position = (vec3)position + camera_settings::movement_speed * up;

//					Axis Z
	if (input::is_pressed_or_held(GLFW_KEY_W))
		position = (vec3)position + camera_settings::movement_speed * front;
	else if (input::is_pressed_or_held(GLFW_KEY_S))
		position = (vec3)position - camera_settings::movement_speed * front;
	recalculate();
}

void					camera::recalculate()
{
	vec3				local_front;

	yaw += input::mouse_offset->x * camera_settings::rotation_speed;
	pitch += input::mouse_offset->y * camera_settings::rotation_speed;

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

	view_matrix = lookAt((vec3)position, (vec3)position + front, up);
	projection_matrix = perspective(
		radians(camera_settings::fov),
		(float)window::size.x / (float)window::size.y,
		camera_settings::near_plane,
		camera_settings::far_plane);
}