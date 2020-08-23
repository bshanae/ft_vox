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

	bool			controlled_by_input = true;
	bool			controlled_by_gravity = false;

	vec3			velocity = vec3(0.f);

	void			update() override;

	void 			process_physics();
	void 			process_movement();
	void 			process_interaction();
	void 			process_ray_casting();

	aabb			aabb(const vec3 &position) const;
	bool			does_collide_with_world(const vec3 &position) const;
};


