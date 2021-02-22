#pragma once

namespace				game
{
	class				skybox_settings;
}

struct					game::skybox_settings
{
	static inline path	source_right = "project/resources/skybox/default/right.jpg";
	static inline path	source_left = "project/resources/skybox/default/left.jpg";
	static inline path	source_top = "project/resources/skybox/default/top.jpg";
	static inline path	source_bottom = "project/resources/skybox/default/bottom.jpg";
	static inline path	source_front = "project/resources/skybox/default/front.jpg";
	static inline path	source_back = "project/resources/skybox/default/back.jpg";
};