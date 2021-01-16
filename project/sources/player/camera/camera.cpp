#include "camera.h"

#include "engine/window/window.h"
#include "engine/input/input.h"
#include "world/world/world.h"

using namespace			engine;
using namespace			player;

						camera::camera()
{
	usual_object::layout = "System";
	usual_object::should_be_rendered = false;

	position = camera_settings::initial_position;
}

vec3					camera::get_position() const
{
	return position;
}

mat4					camera::get_projection_matrix() const
{
	return projection_matrix;
}

mat4					camera::get_view_matrix() const
{
	return view_matrix;
}

bool					camera::did_change() const
{
	return _did_change;
}

vec3					camera::get_front() const
{
	return front;
}

vec3					camera::get_back() const
{
	return (vec3)get_front() * -1.f;
}

vec3					camera::get_up() const
{
	return up;
}

vec3					camera::get_down() const
{
	return (vec3)up * -1.f;
}

vec3					camera::get_left() const
{
	return ((vec3)right * -1.f);
}

vec3					camera::get_right() const
{
	return right;
}

void					camera::set_position(const vec3 &value)
{
	position = value;
	recalculate();
}

void					camera::set_did_change(bool value)
{
	_did_change = value;
}

optional<camera::hit>	camera::cast_ray()
{
	float				x = floor(position.x);
	float				y = floor(position.y);
	float				z = floor(position.z);

	float 				delta_x = front.x;
	float 				delta_y = front.y;
	float 				delta_z = front.z;

	sign				step_x = delta_x >= 0 ? sign::plus : sign::minus;
	sign				step_y = delta_y >= 0 ? sign::plus : sign::minus;
	sign				step_z = delta_z >= 0 ? sign::plus : sign::minus;

	sign				inverted_step_x = delta_x >= 0 ? sign::minus : sign::plus;
	sign				inverted_step_y = delta_y >= 0 ? sign::minus : sign::plus;
	sign				inverted_step_z = delta_z >= 0 ? sign::minus : sign::plus;

	float				t_max_x = intbound(position.x, delta_x);
	float				t_max_y = intbound(position.y, delta_y);
	float				t_max_z = intbound(position.z, delta_z);

	float				t_delta_x = (float)step_x / delta_x;
	float				t_delta_y = (float)step_y / delta_y;
	float				t_delta_z = (float)step_z / delta_z;

	world::block::face	face;
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
			face = world::block::from_axis_and_sign(axis::x, inverted_step_x);
		}
		else if (choice == axis::y)
		{
			y += (float)step_y;
			t_max_y += t_delta_y;
			face = world::block::from_axis_and_sign(axis::y, inverted_step_y);
		}
		else if (choice == axis::z)
		{
			z += (float)step_z;
			t_max_z += t_delta_z;
			face = world::block::from_axis_and_sign(axis::z, inverted_step_z);
		}

		if (auto block = world::world::get_instance()->find_block(vec3(x, y, z)))
		{
			assert(block);
			if ((*block)().is_editable())
				return {(hit){*block, face}};
		}
	}

	return {};
}

void					camera::update()
{
	_did_change = input::get_instance()->did_mouse_move();

	yaw += input::get_instance()->get_mouse_offset().x * camera_settings::rotation_speed;
	pitch += input::get_instance()->get_mouse_offset().y * camera_settings::rotation_speed;

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