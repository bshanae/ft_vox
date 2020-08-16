#include "player.h"

#include "application/input.h"
#include "world/world/world.h"
#include "player/camera/camera.h"

					player::player()
{
	layout = "main";
	should_be_rendered = false;
}

void				player::update()
{
	if (input::is_pressed(GLFW_KEY_ENTER))
	{
		auto 		hit = camera::cast_ray();

		if (hit)
		{
			auto 	axis_and_sign = block::to_axis_and_sign(hit->face);
			auto	neighbor = hit->block.neighbor(axis_and_sign.first, axis_and_sign.second);

			world::remove_block(hit->block);

//			assert(neighbor);
//			world::insert_block(*neighbor, block::type::water);
		}
	}
}