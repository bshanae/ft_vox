#pragma once

#include "common/imports/glm.h"
#include "engine/object/usual_object/usual_object.h"

namespace				ui
{
	class 				font;
	class 				text;
}

class					ui::text : public engine::usual_object<text>
{
public :
						text();
						~text() override = default;

	std::string			get_string() const;
	ivec2				get_position() const;
	shared_ptr<font>	get_font() const;
	ivec2				get_size() const;

	void				set_string(const std::string &string);
	void				set_font(const shared_ptr<font> &font);

private :

	std::string			string;
	ivec2				position;
	shared_ptr<font>	font;
	ivec2				size;

	void				render() override;
	void				recalculate_size();
};


