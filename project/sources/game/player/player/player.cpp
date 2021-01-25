#include "player.h"

#include "engine/main/system/input/input.h"
#include "engine/main/rendering/camera/camera.h"

#include "game/world/world/world.h"
#include "game/player/player/player_settings.h"
#include "game/player/ray_caster/ray_caster.h"

#include "application/common/debug/debug.h"

using namespace 		engine;
using namespace 		game;

						player::player()
{
	set_layout("System");
}

void					player::when_updated()
{
	process_input();
	process_selection();
}

void 					player::process_input()
{
	vec3				movement = vec3(0.f);
	float				speed_up;

	speed_up = input::is_held(input::key::shift)  ? player_settings::speed_up : 1.f;

	if (input::is_pressed_or_held(input::key::letter_a))
		movement += camera::get_left();
	else if (input::is_pressed_or_held(input::key::letter_d))
		movement += camera::get_right();

	if (input::is_pressed_or_held(input::key::letter_w))
		movement += camera::get_front();
	else if (input::is_pressed_or_held(input::key::letter_s))
		movement += camera::get_back();

	if (movement != vec3(0.f))
	{
		movement = normalize(movement) * player_settings::movement_speed * speed_up;
		offset_camera_if_possible(movement);
	}

	if (input::is_held(input::key::space))
		offset_camera_if_possible(player_settings::flight_lift * speed_up);

	if (input::is_pressed(input::key::mouse_left))
	{
		if (auto hit = ray_caster::cast_ray(); hit)
		{
			world::world::remove_block(hit->block);
			force_ray_cast = true;
		}
	}

	if (input::is_pressed(input::key::mouse_right))
	{
		if (auto hit = ray_caster::cast_ray(); hit)
		{
			auto 	axis_and_sign = block::to_axis_and_sign(hit->face);
			auto	neighbor = hit->block.get_neighbor(axis_and_sign.first, axis_and_sign.second);

			if (!debug::check(neighbor != nullopt, "[game::player] Can't put block"))
				return;

			world::world::insert_block(*neighbor, block::dirt_with_grass);

			force_ray_cast = true;
		}
	}
}

void 					player::process_selection()
{
	if (camera::did_change() or force_ray_cast)
	{
		if (auto hit = ray_caster::cast_ray(); hit)
		{
			debug::log("[game::player] Selected block : " + to_string(hit->block.get_world_position()));
			world::world::select_block(hit->block, hit->face);
		}
		else
			world::world::unselect_block();

		force_ray_cast = false;
	}
}

aabb					player::get_aabb(const vec3 &position) const
{
	vec3				min = position;
	vec3				max = position;

	min.x -= player_settings::aabb_size.x / 2.f;
	min.y -= player_settings::aabb_size.y;
	min.z -= player_settings::aabb_size.z / 2.f;

	max.x += player_settings::aabb_size.x / 2.f;
	max.z += player_settings::aabb_size.z / 2.f;

	return {min, max};
}

void					player::offset_camera_if_possible(const vec3 &offset) const
{
	vec3				new_position;

	new_position = (vec3)camera::get_position() + offset;
	if (not world::world::does_collide(get_aabb(new_position)))
		camera::set_position(new_position);
}