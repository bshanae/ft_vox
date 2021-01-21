#include "player.h"

#include "engine/main/system/input/input.h"
#include "engine/main/rendering/camera/camera.h"

#include "game/world/world/world.h"
#include "game/player/player_settings.h"

#include "application/common/debug/logger/logger.h"

using namespace 		debug;
using namespace 		engine;
using namespace 		game;

						player::player()
{
	set_layout("System");
	timer_for_second_space = timer(player_settings::second_space_wait);
}

void					player::when_updated()
{
	process_physics();
	process_input();
	process_selection();
}

void 					player::process_physics()
{
	vec3				position;

#warning "TEMPORARY SOLUTION"
	static bool 		dummy_lock = true;

	if (input::is_pressed_or_held(input::key::number_1))
		dummy_lock = false;

	if (dummy_lock)
		return ;

	if (is_flying)
		return ;

	velocity += player_settings::gravity_force;
	position = camera::get_position() + velocity;

	if (world::world::does_collide(get_aabb(position)))
	{
		velocity = vec3();
		is_jumping = false;
	}
	else
		camera::get_position() = position;
}

void 					player::process_input()
{
	vec3				movement = vec3(0.f);
	float				speed_up;

	speed_up = input::is_held(input::key::shift) and is_flying ? player_settings::speed_up : 1.f;

	if (is_flying)
	{
		if (input::is_pressed_or_held(input::key::letter_a))
			movement += camera::get_left();
		else if (input::is_pressed_or_held(input::key::letter_d))
			movement += camera::get_right();

		if (input::is_pressed_or_held(input::key::letter_w))
			movement += camera::get_front();
		else if (input::is_pressed_or_held(input::key::letter_s))
			movement += camera::get_back();
	}
	else if (not is_jumping)
	{
		if (input::is_pressed_or_held(input::key::letter_a))
			movement += discard_y(camera::get_left());
		else if (input::is_pressed_or_held(input::key::letter_d))
			movement += discard_y(camera::get_right());

		if (input::is_pressed_or_held(input::key::letter_w))
			movement += discard_y(camera::get_front());
		else if (input::is_pressed_or_held(input::key::letter_s))
			movement += discard_y(camera::get_back());
	}

	if (movement != vec3(0.f))
	{
		movement = normalize(movement) * player_settings::movement_speed * speed_up;
		velocity += movement * player_settings::movement_force;

		offset_camera_if_possible(movement);
	}

	if (input::is_pressed(input::key::space))
	{
		if (timer_for_second_space.get_state() == timer::running)
		{
			timer_for_second_space.reset();
			is_flying = not is_flying;
			is_jumping = false;
			velocity = vec3();
		}
		else
		{
			timer_for_second_space.execute();

			if (is_flying)
				offset_camera_if_possible(player_settings::flight_lift * speed_up);
			else if (not is_jumping)
			{
				velocity += player_settings::jump_force;
				is_jumping = true;
			}
		}
	}

	if (input::is_held(input::key::space) and is_flying)
		offset_camera_if_possible(player_settings::flight_lift * speed_up);

	if (input::is_pressed(input::key::mouse_left))
	{
		if (auto hit = camera::cast_ray(); hit)
		{
			world::world::remove_block(hit->block);
			force_ray_cast = true;
		}
	}

	if (input::is_pressed(input::key::mouse_right))
	{
		if (auto hit = camera::cast_ray(); hit)
		{
			auto 	axis_and_sign = block::to_axis_and_sign(hit->face);
			auto	neighbor = hit->block.get_neighbor(axis_and_sign.first, axis_and_sign.second);

			assert(neighbor);
			world::world::insert_block(*neighbor, block::dirt_with_grass);

			force_ray_cast = true;
		}
	}
}

void 					player::process_selection()
{
	if (camera::did_change() or force_ray_cast)
	{
		if (auto hit = camera::cast_ray(); hit)
		{
			logger::log(logger::player, "Selected block : " + to_string(hit->block.world_position()));
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

vec3					player::discard_y(const vec3 &original)
{
	return (vec3(original.x, 0.f, original.z));
}