#include "player.h"

#include "engine/input/input.h"
#include "world/world/world.h"
#include "player/camera/camera.h"
#include "player/player/player_settings.h"

						player::player()
{
	layout = "system";
	should_be_rendered = false;
}

void					player::update()
{
	process_physics();
	process_movement();
	process_interaction();
	process_ray_casting();
}

void 					player::process_physics()
{
	if (not controlled_by_gravity)
		return ;

	vec3				position;

	velocity += player_settings::gravity_force;
	position = (vec3)camera::position + velocity;

	if (does_collide_with_world(position))
	{
		controlled_by_gravity = false;
		controlled_by_input = true;
		velocity = vec3();
	}
	else
		camera::position = position;
}

void 					player::process_movement()
{
	optional<vec3>		movement;

	if (not controlled_by_input)
		return ;

	if (input::is_pressed_or_held(GLFW_KEY_A))
		movement = (vec3)camera::right * -1.f * player_settings::movement_speed;
	else if (input::is_pressed_or_held(GLFW_KEY_D))
		movement = (vec3)camera::right * +1.f * player_settings::movement_speed;

	if (input::is_pressed_or_held(GLFW_KEY_Q))
		movement = (vec3)camera::up * -1.f * player_settings::movement_speed;
	else if (input::is_pressed_or_held(GLFW_KEY_E))
		movement = (vec3)camera::up * +1.f * player_settings::movement_speed;

	if (input::is_pressed_or_held(GLFW_KEY_W))
		movement = (vec3)camera::front * +1.f * player_settings::movement_speed;
	else if (input::is_pressed_or_held(GLFW_KEY_S))
		movement = (vec3)camera::front * -1.f * player_settings::movement_speed;

	if (input::is_pressed(GLFW_KEY_SPACE))
	{
		controlled_by_gravity = true;
		controlled_by_input = false;
		velocity = player_settings::jump_force;
	}

	if (movement)
	{
		const vec3		position = (vec3)camera::position + *movement;
		const ::aabb	aabb = player::aabb(position);

		if (not world::does_collide(aabb))
			camera::position = position;
	}
}

void 					player::process_interaction()
{
	if (input::is_pressed(GLFW_KEY_ENTER))
	{
		if (auto hit = camera::cast_ray(); hit)
		{
			auto 	axis_and_sign = block::to_axis_and_sign(hit->face);
			auto	neighbor = hit->block.neighbor(axis_and_sign.first, axis_and_sign.second);

			assert(neighbor);
			world::insert_block(*neighbor, block::type::dirt_with_grass);

			intentional_ray_cast = true;
		}
	}
}

void 					player::process_ray_casting()
{
	if (camera::have_changed or intentional_ray_cast)
	{
		if (auto hit = camera::cast_ray(); hit)
			world::select_block(hit->block, hit->face);
		else
			world::unselect_block();

		intentional_ray_cast = false;
	}
}

aabb					player::aabb(const vec3 &position) const
{
	return {position - player_settings::aabb_size / 2.f, position +  + player_settings::aabb_size / 2.f};
}

bool					player::does_collide_with_world(const vec3 &position) const
{
	return (world::does_collide(player::aabb(position)));
}