#include "font_library.h"

#include "application/common/debug/debug.h"

using namespace		engine::ui;

					font_library::font_library()
{
	set_layout("System");

	debug::check_critical(FT_Init_FreeType(&library) == 0, "[font_library] Can't initialize instance");
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

				font_library::~font_library()
{
FT_Done_FreeType(library);
}