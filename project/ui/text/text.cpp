#include "text.h"

#include "engine/window/window.h"
#include "ui/font/font.h"
#include "ui/font/symbol.h"

					text::text()
{
	usual_object::layout = "UI";

	string.setter = [this](const ::string &value)
	{
		string.value = value;
		recalculate_size();
	};

	font.setter = [this](const shared_ptr<::font> &value)
	{
		font.value = value;
		recalculate_size();
	};

	string = "EMPTY";
	position = ivec2(0, 0);
	font = nullptr;
}

void 				text::render()
{
	assert(*font);

	ivec2			position_iterator = position;
	vec3			position_of_symbol = vec3(0.f);

	position_iterator = window::invert_y(position_iterator);
	for (char character : *string)
	{
		auto		symbol = (*font)->find_symbol(character);

		auto		bearing = *symbol->bearing;
		auto		advance = *symbol->advance;

		position_of_symbol.x = (float)(position_iterator.x);
		position_of_symbol.y = (float)(position_iterator.y - bearing.y);

		symbol->render(position_of_symbol);

		position_iterator.x += advance + bearing.x;
	}
}

void				text::recalculate_size()
{
	size = vec2(0, 0);

	if (not *font)
		return ;
	for (char character : *string)
	{
		auto 		symbol = (*font)->find_symbol(character);

		size.value.x += symbol->size->x + symbol->advance + symbol->bearing->x;
		size.value.y = max(size->y, symbol->size->y);
	}
}