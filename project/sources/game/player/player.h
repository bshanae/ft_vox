#pragma once

#include "engine/core/object/object/object.h"
#include "engine/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/system/time/timer/timer.h"

#include "game/world/utils/aabb/aabb.h"

namespace			game
{
	class			player;
}

class				game::player :
						public engine::object,
						public engine::unique_object_constructor<game::player>
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

	void			when_updated() override;

	void 			process_physics();
	void 			process_input();
	void 			process_selection();

	aabb			get_aabb(const vec3 &position) const;
	void			offset_camera_if_possible(const vec3 &offset) const;

	static vec3		discard_y(const vec3 &original);
};


