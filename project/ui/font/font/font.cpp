#include "font.h"

#include "ui/font/font_library/font_library.h"
#include "ui/font/symbol/symbol.h"

using namespace			ui;

						font::font(const path &source, const int &width)
{
	auto				library = font_library::instance()->library;

	assert(FT_New_Face(library, source.c_str(), 0, &face) == 0);
	FT_Set_Pixel_Sizes(face, 0, width);
}

shared_ptr<symbol>		font::find_symbol(char task) const
{
	auto				result = map.find(task);

	assert(result != map.end() and "Symbol not found");
	return (result->second);
}

void					font::build_map()
{
	for (int i = 0; i < size_of_map; i++)
		map.emplace(i, build_symbol(static_cast<char>(i)));
}

shared_ptr<symbol>		font::build_symbol(char task)
{
	shared_ptr<symbol>	new_symbol;

	assert(FT_Load_Char(face, task, FT_LOAD_RENDER) == 0);
	new_symbol = make_shared<symbol>(face);
	new_symbol->font = shared_from_this();
	return (new_symbol);
}