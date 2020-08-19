#include "player.h"

#include "core/input/input.h"
#include "world/world/world.h"
#include "player/camera/camera.h"
#include "player/player/player_settings.h"

							player::player()
{
	layout = "system";
	should_be_rendered = false;
}

void						player::update()
{
	if (world::performing_initial_procedure)
		return ;

	process_movement();
	process_interaction();
}

void 						player::process_movement()
{
	if (input::is_pressed_or_held(GLFW_KEY_A))
		camera::move(camera::move_request::left, player_settings::movement_speed);
	else if (input::is_pressed_or_held(GLFW_KEY_D))
		camera::move(camera::move_request::right, player_settings::movement_speed);
//						Axis y
	if (input::is_pressed_or_held(GLFW_KEY_Q))
		camera::move(camera::move_request::down, player_settings::movement_speed);
	else if (input::is_pressed_or_held(GLFW_KEY_E))
		camera::move(camera::move_request::up, player_settings::movement_speed);

//						Axis Z
	if (input::is_pressed_or_held(GLFW_KEY_W))
		camera::move(camera::move_request::forward, player_settings::movement_speed);
	else if (input::is_pressed_or_held(GLFW_KEY_S))
		camera::move(camera::move_request::back, player_settings::movement_speed);
}

void 						player::process_interaction()
{
	bool 					already_casted_ray = false;
	optional<camera::hit>	hit;

	if (camera::have_changed)
	{
		hit = camera::cast_ray();
		already_casted_ray = true;

		world::highlight_block(hit ? optional<block_id>(hit->block) : nullopt);
	}
	if (input::is_pressed(GLFW_KEY_ENTER))
	{
		if (not already_casted_ray)
			hit = camera::cast_ray();

		if (hit)
		{
			auto 	axis_and_sign = block::to_axis_and_sign(hit->face);
			auto	neighbor = hit->block.neighbor(axis_and_sign.first, axis_and_sign.second);

//			world::remove_block(hit->block);
//			world::highlight_block(nullopt);

			assert(neighbor);
			world::insert_block(*neighbor, block::type::water);
			world::highlight_block(*neighbor);
		}
	}
}