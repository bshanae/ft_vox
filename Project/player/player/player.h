#pragma once

#include "engine/object/unique_object.h"
#include "world/aabb/aabb.h"

class				player : public unique_object<player>
{
public :
					player();
					~player() override = default;
private :

	bool			intentional_ray_cast = false;

	enum class		movement_mod
	{
		walk,
		flight
	}				movement_mod;

	vec3			velocity = vec3(0.f);

	void			update() override;

	void 			process_physics();
	void 			process_input();
	void 			process_selection();

	aabb			aabb(const vec3 &position) const;
	bool			does_collide_with_world(const vec3 &position) const;

	static vec3		discard_y_and_normalize(const vec3 &original);
};


