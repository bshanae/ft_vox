#include "info.h"

#include "engine/main/system/window/window/window.h"
#include "engine/main/rendering/camera/camera/camera.h"
#include "engine/extensions/ui/font/font/font.h"
#include "engine/extensions/ui/text/text.h"
#include "engine/extensions/utilities/fps_counter/fps_counter.h"

#include "game/world/world/world_settings.h"
#include "game/player/player/player.h"

using namespace			game::ui;

						info::info()
{
	set_layout("System");
}

void 					info::when_initialized()
{
	const auto			font = engine::ui::font::create("resources/fonts/SFMonoSemibold.otf", 25);
	const auto			fps_position = get_next_label_position();

	const auto			fov_position = get_next_label_position();
	const auto			visibility_position = get_next_label_position();
	const auto			speed_position = get_next_label_position();
	const auto			position_position = get_next_label_position();

	ui_fps = engine::ui::text::create(fps_position, font, "");
	ui_fov = engine::ui::text::create(fov_position, font, "");
	ui_visibility = engine::ui::text::create(visibility_position, font, "");
	ui_speed = engine::ui::text::create(speed_position, font, "");
	ui_position = engine::ui::text::create(position_position, font, "");
}

void 					info::when_updated()
{
	const auto			fps = engine::utilities::fps_counter::get_instance()->get_fps();
	const auto			fov = engine::camera::get_fov();
	const auto			visibility = world_settings::visibility_limit[world_settings::current_visibility_option];
	const auto			speed = player::get_instance()->get_approximate_speed();
	const auto			position = engine::camera::get_position();

	ui_fps->set_string(format_fps(fps));
	ui_fov->set_string(format_fov(fov));
	ui_visibility->set_string(format_visibility(visibility));
	ui_speed->set_string(format_speed(speed));
	ui_position->set_string(format_position(position));
}

ivec2					info::get_next_label_position()
{
	static const auto	panel_offset = ivec2(30, 0);
	static const auto	label_size = ivec2(400, 40);

	static const auto	window_size = engine::window::get_instance()->get_size();

	static int 			number_of_labels = 0;

	return
	{
		window_size.x - panel_offset.x - label_size.x,
		window_size.y - panel_offset.y - label_size.y * ++number_of_labels
	};
}

string					info::format_fps(int fps)
{
	return "FPS : " + to_string(fps);
}

string					info::format_fov(float fov)
{
	return "FOV : " + to_string((int)fov);
}

string					info::format_visibility(float visibility)
{
	return "Visibility : ~" + to_string((int)visibility) + " blocks";
}

string 					info::format_speed(float speed)
{
	if ((int)speed == 0)
		return "Speed : 0 blocks/sec";

	return "Speed : ~" + to_string((int)speed) + " blocks/sec";
}

string 					info::format_position(const vec3 &position)
{
	return
	(
		"Position : " +
		to_string((int)position.x) + ", " +
		to_string((int)position.y) + ", " +
		to_string((int)position.z)
	);
}