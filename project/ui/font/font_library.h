#pragma once

#include "common/freetype.h"
#include "engine/object/unique_object.h"

class 				font;

class				font_library : public unique_object<font_library>
{
	friend class	font;

public :
					font_library()
	{
		unique_object::layout = "System";
		unique_object::should_be_rendered = false;
		unique_object::should_be_updated = false;

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