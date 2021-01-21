#include "camera.h"

#include "engine/system/window/window.h"
#include "engine/system/input/input.h"

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

// TODO Remove this
#include "game/world/utils/array3/array3.h"

optional<camera::hit>	camera::cast_ray()
{
	auto				instance = get_instance();

	float				x = floor(instance->position.x);
	float				y = floor(instance->position.y);
	float				z = floor(instance->position.z);

	float 				delta_x = instance->front.x;
	float 				delta_y = instance->front.y;
	float 				delta_z = instance->front.z;

	sign				step_x = delta_x >= 0 ? sign::plus : sign::minus;
	sign				step_y = delta_y >= 0 ? sign::plus : sign::minus;
	sign				step_z = delta_z >= 0 ? sign::plus : sign::minus;

	sign				inverted_step_x = delta_x >= 0 ? sign::minus : sign::plus;
	sign				inverted_step_y = delta_y >= 0 ? sign::minus : sign::plus;
	sign				inverted_step_z = delta_z >= 0 ? sign::minus : sign::plus;

	float				t_max_x = intbound(instance->position.x, delta_x);
	float				t_max_y = intbound(instance->position.y, delta_y);
	float				t_max_z = intbound(instance->position.z, delta_z);

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

		if (auto block = game::world::find_block(vec3(x, y, z)))
		{
			assert(block);
			if ((*block)().is_editable())
				return {(hit){*block, face}};
		}
	}

	return {};
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