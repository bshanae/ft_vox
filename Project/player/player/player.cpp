#include "player.h"

#include "application/input.h"
#include "world/world/world.h"
#include "player/camera/camera.h"

							player::player()
{
	layout = "system";
	should_be_rendered = false;
}

void						player::update()
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

			world::remove_block(hit->block);
			world::highlight_block(nullopt);

//			assert(neighbor);
//			world::insert_block(*neighbor, block::type::water);
		}
	}
}