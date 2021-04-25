#include "text.h"

#include "engine/extensions/ui/font/font/font.h"
#include "engine/extensions/ui/font/symbol/symbol.h"
#include "engine/main/system/window/window/window.h"
#include "engine/main/system/window/window_tools/window_tools.h"

using namespace		engine;
using namespace		engine::ui;

					text::text(const ivec2 &position, const shared_ptr<class font> &font, const std::string &string) :
						position(position),
						font(font),
						string(string)
{
	set_layout("UI");
}

std::string			text::get_string() const
{
	return string;
}

ivec2				text::get_position() const
{
	return position;
}

shared_ptr<font>	text::get_font() const
{
	return font;
}

ivec2				text::get_size() const
{
	return size;
}


void				text::set_string(const std::string &string)
{
	this->string = string;
	recalculate_size();
}

void 				text::when_rendered()
{
	if (font == nullptr)
	{
		debug::raise_warning("[text] Can't render, because font is not set");
		return;
	}

	ivec2			position_iterator = position;
	vec3			position_of_symbol = vec3(0.f);

	position_iterator = window_tools::invert_y(position_iterator);
	for (char character : string)
	{
		auto		symbol = font->find_symbol(character);

		if (!symbol)
			continue;

		auto		bearing = symbol->get_bearing();
		auto		advance = symbol->get_advance();

		position_of_symbol.x = (float)(position_iterator.x + bearing.x);
		position_of_symbol.y = (float)(position_iterator.y - bearing.y);

		symbol->render(position_of_symbol);

		position_iterator.x += advance;
	}
}

void				text::recalculate_size()
{
	ivec2			new_size = vec2(0, 0);

	if (not font)
		return ;

	for (char character : string)
	{
		const auto	symbol = font->find_symbol(character);

		if (!symbol)
			continue;

		new_size.x += symbol->get_size().x + symbol->get_advance() + symbol->get_bearing().x;
		new_size.y = max(new_size.y, symbol->get_size().y);
	}

	size = new_size;
}