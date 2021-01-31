#include "ray_caster.h"

#include "engine/main/rendering/camera/camera.h"

#include "game/world/chunk/block/block_face/block_face.h"
#include "game/player/ray_caster/ray_caster_settings.h"
#include "game/world/world/world.h"

using namespace				game;

float						intbound(float s, float ds)
{
	if (ds < 0)
		return (intbound(-s, -ds));
	else
	{
		s = fmod((fmod(s, 1.f) + 1), 1.f);
		return ((1.f - s) / ds);
	}
}

optional<ray_caster::hit>	ray_caster::cast_ray()
{
	const auto				camera = engine::camera::get_instance();

	float					x = floor(camera->get_position().x);
	float					y = floor(camera->get_position().y);
	float					z = floor(camera->get_position().z);

	const float 			delta_x = camera->get_front().x;
	const float 			delta_y = camera->get_front().y;
	const float 			delta_z = camera->get_front().z;

	const sign				step_x = delta_x >= 0 ? sign::plus : sign::minus;
	const sign				step_y = delta_y >= 0 ? sign::plus : sign::minus;
	const sign				step_z = delta_z >= 0 ? sign::plus : sign::minus;

	const sign				inverted_step_x = delta_x >= 0 ? sign::minus : sign::plus;
	const sign				inverted_step_y = delta_y >= 0 ? sign::minus : sign::plus;
	const sign				inverted_step_z = delta_z >= 0 ? sign::minus : sign::plus;

	float					t_max_x = intbound(camera->get_position().x, delta_x);
	float					t_max_y = intbound(camera->get_position().y, delta_y);
	float					t_max_z = intbound(camera->get_position().z, delta_z);

	const float				t_delta_x = (float)step_x / delta_x;
	const float				t_delta_y = (float)step_y / delta_y;
	const float				t_delta_z = (float)step_z / delta_z;

	block_face			face;
	axis				choice;

	for (int i = 0; i < ray_caster_settings::ray_cast_limit; i++)
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
			face = from_axis_and_sign(axis::x, inverted_step_x);
		}
		else if (choice == axis::y)
		{
			y += (float)step_y;
			t_max_y += t_delta_y;
			face = from_axis_and_sign(axis::y, inverted_step_y);
		}
		else if (choice == axis::z)
		{
			z += (float)step_z;
			t_max_z += t_delta_z;
			face = from_axis_and_sign(axis::z, inverted_step_z);
		}

		if (auto block = game::world::find_block(vec3(x, y, z)))
		{
			if (!block)
				return {};

			if (is_editable(get_meta_type((*block)().type)))
				return {(hit){*block, face}};
		}
	}

	return {};
}
