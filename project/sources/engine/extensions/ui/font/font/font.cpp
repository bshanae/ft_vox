#include "font.h"

#include "engine/extensions/ui/font/font_library/font_library.h"
#include "engine/extensions/ui/font/symbol/symbol.h"

#include "application/common/debug/debug.h"

using namespace			engine::ui;

						font::font(const path &source, const int &width)
{
	auto				library = font_library::get_instance()->library;

	debug::check_critical(FT_New_Face(library, source.c_str(), 0, &face) == 0, "[font] Can't initialize instance");
	FT_Set_Pixel_Sizes(face, 0, width);
}

shared_ptr<symbol>		font::find_symbol(char task) const
{
	auto				result = map.find(task);

	if (result == map.end())
	{
		debug::raise_warning("[font] Symbol '" + string(1, task) + "'not found");
		return nullptr;
	}

	return result->second;
}

void					font::build_map()
{
	for (int i = 0; i < size_of_map; i++)
		map.emplace(i, build_symbol(static_cast<char>(i)));
}

shared_ptr<symbol>		font::build_symbol(char task)
{
	shared_ptr<symbol>	new_symbol;

	debug::check_critical
	(
		FT_Load_Char(face, task, FT_LOAD_RENDER) != 0,
		"[font] Can't build symbol '" + string(1, task) + "'"
	);

	new_symbol = make_shared<symbol>(face);
	new_symbol->font = shared_from_this();
	return new_symbol;
}