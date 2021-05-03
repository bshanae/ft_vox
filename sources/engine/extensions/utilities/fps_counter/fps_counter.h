#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/main/system/time/timer/timer.h"

namespace			engine::utilities
{
	class 			fps_counter;
}

class 				engine::utilities::fps_counter :
						public engine::object,
						public engine::unique_object_constructor<engine::utilities::fps_counter>
{
public :
					fps_counter();
					~fps_counter() override = default;

	int				get_fps() const;

private :

	int 			frames_count;
	timer			timer;

	int				last_fps;

	void 			when_updated() override;
};