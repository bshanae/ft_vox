#pragma once

#include "engine/object/unique_object.h"
#include "world/aabb/aabb.h"

class				player : public unique_object<player>
{
public :
					player();
					~player() override = default;
private :

	bool			force_ray_cast = false;

	void			update() override;

	void 			process_movement();
	void 			process_interaction();
	void 			process_ray_casting();

	aabb			aabb(const vec3 &position) const;
};


