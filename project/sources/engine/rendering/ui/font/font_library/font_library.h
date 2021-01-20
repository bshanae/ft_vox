#pragma once

#include "engine/core/object/object/object.h"
#include "engine/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

#include "application/common/imports/freetype.h"

namespace			ui
{
	class 			font;

	class 			font_library;
}

class				ui::font_library :
						public engine::object,
						public engine::unique_object_constructor<font_library>
{
	friend class	ui::font;

public :
					font_library()
	{
		set_layout("System");

		assert(FT_Init_FreeType(&library) == 0);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}

					~font_library() override
	{
		FT_Done_FreeType(library);
	}

private :

	FT_Library		library = nullptr;
};