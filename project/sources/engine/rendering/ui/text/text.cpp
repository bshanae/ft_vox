#include "text.h"

#include "engine/rendering/ui/font/font/font.h"
#include "engine/rendering/ui/font/symbol/symbol.h"
#include "engine/system/window/window.h"

using namespace		engine;
using namespace		ui;

					text::text()
{
	usual_object::layout = "UI";

	string = "EMPTY";
	position = ivec2(0, 0);
	font = nullptr;
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

void				text::set_font(const shared_ptr<ui::font> &font)
{
	this->font = font;
	recalculate_size();
}

void 				text::render()
{
	assert(font);

	ivec2			position_iterator = position;
	vec3			position_of_symbol = vec3(0.f);

	position_iterator = window::get_instance()->invert_y(position_iterator);
	for (char character : string)
	{
		auto		symbol = font->find_symbol(character);

		auto		bearing = symbol->get_bearing();
		auto		advance = symbol->get_advance();

		position_of_symbol.x = (float)(position_iterator.x);
		position_of_symbol.y = (float)(position_iterator.y - bearing.y);

		symbol->render(position_of_symbol);

		position_iterator.x += advance + bearing.x;
	}
}

void				text::recalculate_size()
{
	ivec2			new_size = vec2(0, 0);

	if (not font)
		return ;

	for (char character : string)
	{
		auto 		symbol = font->find_symbol(character);

		new_size.x += symbol->get_size().x + symbol->get_advance() + symbol->get_bearing().x;
		new_size.y = max(new_size.y, symbol->get_size().y);
	}

	size = new_size;
}