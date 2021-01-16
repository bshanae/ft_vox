#pragma once

#include "engine/core/object/inheritor_object/inheritor_object.h"
#include "engine/rendering/ui/font/font/font.h"
#include "engine/rendering/ui/text/text.h"

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




