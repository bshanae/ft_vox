#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/object_constructor/object_constructor.h"

#include "application/common/imports/glm.h"

namespace				engine::ui
{
	class 				font;
	class 				text;
}

class					engine::ui::text :
							public engine::object,
							public engine::object_constructor<engine::ui::text>
{
public :
						text(const ivec2 &position, const shared_ptr<font> &font, const string &string);
						~text() override = default;

	std::string			get_string() const;
	ivec2				get_position() const;
	shared_ptr<font>	get_font() const;
	ivec2				get_size() const;

	void				set_string(const string &string);

private :

	std::string			string;
	ivec2				position;
	shared_ptr<font>	font;
	ivec2				size;

	void				when_rendered() override;
	void				recalculate_size();
};


