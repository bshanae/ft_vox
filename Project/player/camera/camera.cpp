#include "camera.h"

#include "common/debug.h"
#include "engine/window/window.h"
#include "engine/input/input.h"
#include "world/world/world.h"

						camera::camera()
{
	object_template::layout = "system";
	object_template::should_be_rendered = false;

	position.setter = [this](const vec3 &value)
	{
		position.value = value;
		recalculate();
	};

	position = camera_settings::initial_position;
}

optional<camera::hit>	camera::cast_ray()
{
	float				x = floor(position->x);
	float				y = floor(position->y);
	float				z = floor(position->z);

	float 				delta_x = instance()->front.x;
	float 				delta_y = instance()->front.y;
	float 				delta_z = instance()->front.z;

	sign				step_x = delta_x >= 0 ? sign::plus : sign::minus;
	sign				step_y = delta_y >= 0 ? sign::plus : sign::minus;
	sign				step_z = delta_z >= 0 ? sign::plus : sign::minus;

	sign				inverted_step_x = delta_x >= 0 ? sign::minus : sign::plus;
	sign				inverted_step_y = delta_y >= 0 ? sign::minus : sign::plus;
	sign				inverted_step_z = delta_z >= 0 ? sign::minus : sign::plus;

	float				t_max_x = intbound(position->x, delta_x);
	float				t_max_y = intbound(position->y, delta_y);
	float				t_max_z = intbound(position->z, delta_z);

	float				t_delta_x = (float)step_x / delta_x;
	float				t_delta_y = (float)step_y / delta_y;
	float				t_delta_z = (float)step_z / delta_z;

	block::face			face;
	axis				choice;

	for (int i = 0; i < camera_settings::ray_cast_limit; i++)
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
			x += (float)step_x;
			t_max_x += t_delta_x;
			face = block::from_axis_and_sign(axis::x, inverted_step_x);
		}
		else if (choice == axis::y)
		{
			y += (float)step_y;
			t_max_y += t_delta_y;
			face = block::from_axis_and_sign(axis::y, inverted_step_y);
		}
		else if (choice == axis::z)
		{
			z += (float)step_z;
			t_max_z += t_delta_z;
			face = block::from_axis_and_sign(axis::z, inverted_step_z);
		}

		if (auto block = world::find_block(vec3(x, y, z)))
		{
			assert(block);
			if (not (*block)().is_empty())
				return {(hit){*block, face}};
		}
	}

	return {};
}

void					camera::update()
{
	have_changed = input::have_mouse_moved();

	yaw += input::mouse_offset->x * camera_settings::rotation_speed;
	pitch += input::mouse_offset->y * camera_settings::rotation_speed;

	if (have_changed)
		recalculate();
}

void					camera::move(move_request request, float speed)
{
	instance()->move_non_static(request, speed);
}

void					camera::move_non_static(move_request request, float speed)
{
	switch (request)
	{
		case (move_request::left) :
			position = (vec3)position - speed * right;
			break ;

		case (move_request::right) :
			position = (vec3)position + speed * right;
			break ;

		case (move_request::forward) :
			position = (vec3)position + speed * front;
			break ;

		case (move_request::back) :
			position = (vec3)position - speed * front;
			break ;

		case (move_request::up) :
			position = (vec3)position + speed * up;
			break ;

		case (move_request::down) :
			position = (vec3)position - speed * up;
			break ;

	}

	have_changed = true;
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
	right = normalize(cross(front, up_const));
	up = normalize(cross(right, front));

	view_matrix = lookAt((vec3)position, (vec3)position + front, up);
	projection_matrix = perspective(
		radians(camera_settings::fov),
		(float)window::size.x / (float)window::size.y,
		camera_settings::near_plane,
		camera_settings::far_plane);
}

float					camera::intbound(float s, float ds)
{
	if (ds < 0)
		return (intbound(-s, -ds));
	else
	{
		s = fmod((fmod(s, 1.f) + 1), 1.f);
		return ((1.f - s) / ds);
	}
}