#include "player.h"

#include "engine/input/input.h"
#include "world/world/world.h"
#include "player/camera/camera.h"
#include "player/player/player_settings.h"

						player::player()
{
	layout = "System";
	should_be_rendered = false;
	timer_for_second_space = timer(player_settings::second_space_wait);
}

void					player::update()
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

	if (flying)
		return ;

	velocity += player_settings::gravity_force;
	position = (vec3)camera::position + velocity;

	if (world::does_collide(player::aabb(position)))
		velocity = vec3();
	else
		camera::position = position;
}

void 					player::process_input()
{
	vec3				movement = vec3(0.f);

	if (flying)
	{
		if (input::is_pressed_or_held(input::key::letter_a))
			movement += (vec3)camera::left * player_settings::movement_speed;
		else if (input::is_pressed_or_held(input::key::letter_d))
			movement += (vec3)camera::right * player_settings::movement_speed;

		if (input::is_pressed_or_held(input::key::letter_w))
			movement += (vec3)camera::front * player_settings::movement_speed;
		else if (input::is_pressed_or_held(input::key::letter_s))
			movement += (vec3)camera::back * player_settings::movement_speed;
	}
	else
	{
		if (input::is_pressed_or_held(input::key::letter_a))
			movement += discard_y_and_normalize(camera::left) * player_settings::movement_speed;
		else if (input::is_pressed_or_held(input::key::letter_d))
			movement += discard_y_and_normalize(camera::right) * player_settings::movement_speed;

		if (input::is_pressed_or_held(input::key::letter_w))
			movement += discard_y_and_normalize(camera::front) * player_settings::movement_speed;
		else if (input::is_pressed_or_held(input::key::letter_s))
			movement += discard_y_and_normalize(camera::back) * player_settings::movement_speed;
	}

	if (movement != vec3(0.f))
		offset_camera_if_possible(movement);

	if (input::is_pressed(input::key::space))
	{
		if (timer_for_second_space.state == timer::state::running)
		{
			timer_for_second_space.reset();
			flying = not flying;
		}
		else
		{
			timer_for_second_space.execute();

			if (flying)
				offset_camera_if_possible(player_settings::flight_lift);
			else
				velocity = player_settings::jump_force;
		}
	}

	if (input::is_held(input::key::space))
	{
		if (flying)
			offset_camera_if_possible(player_settings::flight_lift);
	}

	if (input::is_pressed(input::key::mouse_left))
	{
		if (auto hit = camera::cast_ray(); hit)
		{
			world::remove_block(hit->block);
			force_ray_cast = true;
		}
	}

	if (input::is_pressed(input::key::mouse_right))
	{
		if (auto hit = camera::cast_ray(); hit)
		{
			auto 	axis_and_sign = block::to_axis_and_sign(hit->face);
			auto	neighbor = hit->block.neighbor(axis_and_sign.first, axis_and_sign.second);

			assert(neighbor);
			world::insert_block(*neighbor, block::type::dirt_with_grass);

			force_ray_cast = true;
		}
	}
}

void 					player::process_selection()
{
	if (camera::have_changed or force_ray_cast)
	{
		if (auto hit = camera::cast_ray(); hit)
			world::select_block(hit->block, hit->face);
		else
			world::unselect_block();

		force_ray_cast = false;
	}
}

aabb					player::aabb(const vec3 &position) const
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
	const vec3			new_position = (vec3)camera::position + offset;

	if (not world::does_collide(player::aabb(new_position)))
		camera::position = new_position;
}

vec3					player::discard_y_and_normalize(const vec3 &original)
{
	return (glm::normalize(vec3(original.x, 0.f, original.z)));
}