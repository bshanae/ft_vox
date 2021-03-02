#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/main/rendering/camera/camera_event/camera_event.h"
#include "engine/main/system/time/timer/timer.h"

#include "game/world/tools/aabb/aabb.h"
#include "game/world/block/block_type/block_type/block_type.h"

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
	block_type		last_removed_block_type = block_type::air;

	void			when_initialized() override;
	void			when_updated() override;
	void			when_notified(const engine::camera_event &event) override;

	void 			process_input();
	void 			process_selection();

	void			try_place_block();
	void			try_remove_block();

	static vec3		calculate_initial_position();

	aabb			get_aabb(const vec3 &position) const;
	void			offset_camera_if_possible(const vec3 &offset) const;
};


