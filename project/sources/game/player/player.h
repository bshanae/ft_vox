#pragma once

#include "engine/core/object/unique_object/unique_object.h"
#include "engine/system/time/timer/timer.h"

#include "game/world/utils/aabb/aabb.h"

namespace			player
{
	class			player;
}

class				player::player : public engine::unique_object<player>
{
public :
					player();
					~player() override = default;
private :

	bool			force_ray_cast = false;

	bool 			is_jumping = false;
	bool 			is_flying = false;

	engine::timer	timer_for_second_space;

	vec3			velocity = vec3(0.f);

	void			update() override;

	void 			process_physics();
	void 			process_input();
	void 			process_selection();

	world::aabb		get_aabb(const vec3 &position) const;
	void			offset_camera_if_possible(const vec3 &offset) const;

	static vec3		discard_y(const vec3 &original);
};


