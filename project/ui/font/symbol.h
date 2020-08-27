#pragma once

#include "common/opengl.h"
#include "common/glm.h"
#include "common/freetype.h"
#include "common/aliases.h"

class 					font;

class					symbol
{
	friend class		font;

public :

	explicit			symbol(FT_Face &face);
						~symbol() = default;
private :

	shared_ptr<font>	font;

	GLuint				texture;

	ivec2				size;
	ivec2				bearing;
	int					advance;
};


