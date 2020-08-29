#include "text.h"

#include "engine/window/window.h"
#include "ui/font/font.h"
#include "ui/font/symbol.h"

					text::text()
{
	usual_object::layout = "UI";

	string = "EMPTY";
	position = vec2(0, 0);
	font = nullptr;
}

void 				text::render()
{
	assert(*font);

	ivec2			position_iterator = window::to_absolute(position);
	vec3			position_of_symbol = vec3(0.f);

	for (char character : *string)
	{
		auto		symbol = (*font)->find_symbol(character);

		auto		size = *symbol->size;
		auto		bearing = *symbol->bearing;
		auto		advance = *symbol->advance;

		position_of_symbol.x = (float)(position_iterator.x + bearing.x) + (float)size.x / 2.f;
		position_of_symbol.y = (float)(position_iterator.y - bearing.y) + (float)size.y / 2.f;

		symbol->render(position_of_symbol);

		position_iterator.x += advance;
	}
}