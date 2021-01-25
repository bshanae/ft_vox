#pragma once

#include "engine/main/core/object/object/object.h"
#include "engine/main/core/object/object_constructor/unique_object_constructor/unique_object_constructor.h"

#include "application/common/imports/freetype.h"

namespace			engine::ui
{
	class 			font;

	class 			font_library;
}

class				engine::ui::font_library :
						public engine::object,
						public engine::unique_object_constructor<font_library>
{
	friend class	font;

public :
					font_library();
					~font_library() override;

private :

	FT_Library		library = nullptr;
};