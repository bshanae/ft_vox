#include "player.h"

#include "application/common/debug/debug.h"

#include "engine/main/system/input/input.h"
#include "engine/main/rendering/camera/camera/camera.h"

#include "game/world/block/block_face/block_face.h"
#include "game/world/world/world.h"
#include "game/world/chunk/generation/utilities/biome/biome_generator/biome_generator.h"
#include "game/world/chunk/generation/utilities/height_interpolator/height_interpolator.h"
#include "game/player/player/player_settings.h"
#include "game/player/ray_caster/ray_caster.h"

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

void					player::when_initialized()
{
	camera::get_instance()->subscribe(*this);
	camera::set_position(calculate_initial_position());
}

void 					player::when_notified(const engine::camera_event &event)
{
	should_cast_ray = true;
}

void 					player::process_input()
{
	if (engine::input::is_held(engine::input::key::command))
		return;

	// Movement
	{
		vec3			movement_direction = vec3(0.f);

		if (input::is_pressed_or_held(input::key::letter_a))
			movement_direction += camera::get_left();
		else if (input::is_pressed_or_held(input::key::letter_d))
			movement_direction += camera::get_right();

		if (input::is_pressed_or_held(input::key::letter_w))
			movement_direction += camera::get_front();
		else if (input::is_pressed_or_held(input::key::letter_s))
			movement_direction += camera::get_back();

		if (movement_direction != vec3(0.f))
			move(movement_direction, input::is_held(input::key::shift));

		if (input::is_held(input::key::space))
			lift(input::is_held(input::key::shift));
	}

	// Block interaction
	{
		if (input::is_pressed(input::key::mouse_left))
			try_remove_block();

		if (input::is_pressed(input::key::mouse_right))
			try_place_block();
	}
}

void 					player::process_selection()
{
	if (world::world::does_collide(get_aabb(camera::get_position())))
	{
		world::world::unselect_block();
	}
	else if (should_cast_ray)
	{
		if (auto hit = ray_caster::cast_ray(); hit)
		{
			debug::log("[player] Selected block at " + to_string(hit->block.get_world_position()));
			world::world::select_block(hit->block, hit->face);
		}
		else
			world::world::unselect_block();

		should_cast_ray = false;
	}
}

void 					player::move(const vec3 &direction, const bool speed_up)
{
	static const float	speed_transformation = 1.f / 60.f;

	offset_camera_if_possible
	(
		normalize(direction) *
		player_settings::movement_speed *
		speed_transformation *
		(speed_up ? player_settings::speed_up : 1.f)
	);
}

void 					player::lift(bool speed_up)
{
	static const float	speed_transformation = 1.f / 60.f;

	offset_camera_if_possible
	(
		player_settings::flight_lift *
		speed_transformation *
		(speed_up ? player_settings::speed_up : 1.f)
	);
}

void					player::try_place_block()
{
	if (auto hit = ray_caster::cast_ray(); hit)
	{
		auto 			axis_and_sign = to_axis_and_sign(hit->face);
		auto			neighbor = hit->block.get_neighbor(axis_and_sign.first, axis_and_sign.second);

		if (not debug::check(neighbor != nullptr, "[player] Can't put block"))
			return;

		world::world::insert_block(neighbor, last_removed_block_type);

		if (world::world::does_collide(get_aabb(camera::get_position())))
			world::world::remove_block(neighbor);
		else
			should_cast_ray = true;
	}
}

void					player::try_remove_block()
{
	if (auto hit = ray_caster::cast_ray(); hit)
	{
		last_removed_block_type = hit->block->get_type();
		should_cast_ray = true;

		world::world::remove_block(hit->block);
	}
}

vec3					player::calculate_initial_position()
{
	static const auto	height_generator = [](const vec2 &position)
	{
		return biome_generator::generate_biome(position)->generate_height(position);
	};

	const auto 			column = vec2();
	const auto			&biome = biome_generator::generate_biome(column);
	const auto			interpolated_height = height_interpolator(height_generator)(column);

	static const float	tree_like_offset = 7.f;
	static const float	one_block_offset = 1.f;

	vec3				position;

	position.x = 0.5f;
	position.z = 0.5f;
	position.y = (float)interpolated_height + one_block_offset + tree_like_offset + player_settings::aabb_size.y;

	return position;
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
	const vec3			new_position = (vec3)camera::get_position() + offset;

#if FT_VOX_COLLISION_CHECK
	if (not world::world::does_collide(get_aabb(new_position)))
		camera::set_position(new_position);
#else
	camera::set_position(new_position);
#endif
}