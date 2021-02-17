#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"
#include "engine/main/system/time/timestamp/timestamp.h"

namespace					engine::utilities
{
	class 					debug;
}

class						engine::utilities::debug final :
								public engine::object,
								public engine::unique_object_constructor<engine::utilities::debug>
{
public :
							debug();
							~debug() override = default;
private :

	static constexpr bool	print_average_fps = true;
	static constexpr bool	exit_after_some_time = true;
	static constexpr float	exit_time = 5.f;

	int 					total_frames_count;
	timestamp				start_timestamp;

	void 					when_updated() override;

	float					get_average_fps();
};


