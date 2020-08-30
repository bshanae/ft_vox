#pragma once

#include "engine/object/inheritor_object.h"
#include "ui/font/font.h"
#include "ui/text/text.h"

class 				font;

class				button : public inheritor_object<button, text>
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




