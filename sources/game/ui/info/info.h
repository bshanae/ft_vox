#pragma once

#include "application/common/imports/glm.h"
#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

namespace							engine::ui
{
	class 							text;
}

namespace							game::ui
{
	class							info;
}

class								game::ui::info :
										public engine::object,
										public engine::unique_object_constructor<game::ui::info>
{
public :

									info();
									~info() override = default;

private :

	shared_ptr<engine::ui::text>	ui_fps;
	shared_ptr<engine::ui::text>	ui_fov;
	shared_ptr<engine::ui::text>	ui_visibility;
	shared_ptr<engine::ui::text>	ui_speed;
	shared_ptr<engine::ui::text>	ui_position;

	void 							when_initialized() override;
	void 							when_updated() override;

	static ivec2					get_next_label_position();

	static string					format_fps(int fps);
	static string					format_fov(float fov);
	static string					format_visibility(float visibility);
	static string 					format_speed(float speed);
	static string 					format_position(const vec3 &position);
};