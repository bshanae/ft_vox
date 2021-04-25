#pragma once

namespace					game
{
	class					skybox_settings;
}

struct						game::skybox_settings
{
	static inline string	source_right = "resources/skybox/default/right.jpg";
	static inline string	source_left = "resources/skybox/default/left.jpg";
	static inline string	source_top = "resources/skybox/default/top.jpg";
	static inline string	source_bottom = "resources/skybox/default/bottom.jpg";
	static inline string	source_front = "resources/skybox/default/front.jpg";
	static inline string	source_back = "resources/skybox/default/back.jpg";
};