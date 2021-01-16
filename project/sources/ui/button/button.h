#pragma once

#include "engine/object/inheritor_object/inheritor_object.h"
#include "ui/font/font/font.h"
#include "ui/text/text.h"

namespace					ui
{
	class 					font;
	class					button;
}

class						ui::button : public engine::inheritor_object<button, text>
{
public :
							button();
							~button() override = default;

	void 					set_callback(const function<void(void)> &callback);
	ivec2					get_extends() const;

private :

	function<void(void)>	callback;
	ivec2					extends;

	void 					update() override;
	bool					is_inside(const vec2 &point);
};




