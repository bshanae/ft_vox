#pragma once

#include "engine/object/unique_object.h"
#include "engine/time/timer.h"
#include "world/aabb/aabb.h"

class				player : public unique_object<player>
{
public :
					player();
					~player() override = default;
private :

	bool			force_ray_cast = false;
	bool 			flying = false;

	timer			timer_for_second_space;

	vec3			velocity = vec3(0.f);

	void			update() override;

	void 			process_physics();
	void 			process_input();
	void 			process_selection();

	aabb			aabb(const vec3 &position) const;
	void			offset_camera_if_possible(const vec3 &offset) const;

	static vec3		discard_y_and_normalize(const vec3 &original);
};

