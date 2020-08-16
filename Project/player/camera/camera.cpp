#include "camera.h"

#include "common/debug.h"
#include "application/window.h"
#include "application/input.h"
#include "world/world/world.h"

					camera::camera()
{
	object_template::layout = "main";
	object_template::should_be_rendered = false;

	position.setter = [this](const vec3 &value)
	{
		position.value = value;
		recalculate();
	};

	position = camera_settings::initial_position;
}

optional<block_id>	camera::cast_ray() const
{
	float			x = floor(position->x);
	float			y = floor(position->y);
	float			z = floor(position->z);

	float 			delta_x = front.x;
	float 			delta_y = front.y;
	float 			delta_z = front.z;

	float			step_x = delta_x >= 0 ? +1.f : -1.f;
	float			step_y = delta_y >= 0 ? +1.f : -1.f;
	float			step_z = delta_z >= 0 ? +1.f : -1.f;

	float			t_max_x = intbound(position->x, delta_x);
	float			t_max_y = intbound(position->y, delta_y);
	float			t_max_z = intbound(position->z, delta_z);

	float			t_delta_x = step_x / delta_x;
	float			t_delta_y = step_y / delta_y;
	float			t_delta_z = step_z / delta_z;

	vec3			face = vec3(0.f);
	axis			choice;

	for (int i = 0; i < 10; i++)
	{
		if (t_max_x < t_max_y)
		{
			if (t_max_x < t_max_z)
				choice = axis::x;
			else
				choice = axis::z;
		}
		else
		{
			if (t_max_y < t_max_z)
				choice = axis::y;
			else
				choice = axis::z;
		}

		if (choice == axis::x)
		{
			x += step_x;
			t_max_x += t_delta_x;
		}
		else if (choice == axis::y)
		{
			y += step_y;
			t_max_y += t_delta_y;
		}
		else if (choice == axis::z)
		{
			z += step_z;
			t_max_z += t_delta_z;
		}

		if (auto block = world::find_block(vec3(x, y, z)))
		{
			assert(block);
			if (not (*block)().is_empty())
				return (block);
		}
	}

	return {};
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

void				camera::recalculate()
{
	vec3			local_front;

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

float				camera::intbound(float s, float ds)
{
	if (ds < 0)
		return (intbound(-s, -ds));
	else
	{
		s = fmod(s, 1);
		return ((1 - s) / ds);
	}
}