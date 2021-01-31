#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/main/rendering/camera/camera_event/camera_event.h"
#include "engine/main/system/time/timer/timer.h"

#include "game/world/tools/aabb/aabb.h"

namespace			game
{
	class			player;
}

class				game::player :
						public engine::object,
						public engine::unique_object_constructor<game::player>,
						public listener<engine::camera_event>
{
public :
					player();
					~player() override = default;
private :

	bool			should_cast_ray = false;

	void			when_updated() override;
	void			when_notified(const engine::camera_event &event) override;

	void 			process_input();
	void 			process_selection();

	aabb			get_aabb(const vec3 &position) const;
	void			offset_camera_if_possible(const vec3 &offset) const;
};


