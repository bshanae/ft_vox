#pragma once

#include "engine/object/inheritor_object/inheritor_object.h"
#include "ui/font/font/font.h"
#include "ui/text/text.h"

namespace			ui
{
	class 			font;

	class			button;
}

class				ui::button : public engine::inheritor_object<button, text>
{
public :
					button();
					~button() override = default;

					property<write_only, function<void(void)>, button>
					callback;

					property<read_write, ivec2, button>
					extends;

private :

	void 			update() override;

	bool			is_inside(const vec2 &point);
};




