#pragma once

#include "common/opengl.h"
#include "common/glm.h"
#include "common/freetype.h"
#include "common/aliases.h"
#include "common/property.h"
#include "engine/model/texture.h"

class 									font;

class									symbol : public texture
{
	friend class						font;

public :

	explicit							symbol(FT_Face &face);
										~symbol() = default;

	property<read_only, ivec2, symbol>	size;
	property<read_only, ivec2, symbol>	bearing;
	property<read_only, int, symbol>	advance;

	void 								render(const ivec2 &position);

private :

	shared_ptr<font>					font;
};


