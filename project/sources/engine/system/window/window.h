#pragma once

#include "application/common/templates/singleton/singleton.h"
#include "application/common/imports/opengl.h"
#include "application/common/imports/glm.h"
#include "application/common/imports/std.h"

namespace					engine
{
	class					window;
}

class						engine::window : public singleton<window>
{
public :

	static inline string	title = "";
	static inline ivec2		size = ivec2(1280, 720);

							window();
							~window() override;
public :

	vec2					get_mouse_position() const;

	bool					is_closed() const;
	void 					close();

	void 					swap_buffers();
	void 					use_depth_test(bool state);

	vec2					to_normal(const ivec2 &value) const;
	ivec2					to_absolute(const vec2 &value) const;
	ivec2					invert_y(const vec2 &value) const;

private :

	GLFWwindow				*glfw_window = nullptr;
};
