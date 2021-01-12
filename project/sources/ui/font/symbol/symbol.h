#pragma once

#include "common/imports/opengl.h"
#include "common/imports/glm.h"
#include "common/imports/freetype.h"
#include "common/aliases.h"
#include "common/classes/property.h"
#include "engine/model/texture/texture.h"

namespace								ui
{
	class								font;

	class								symbol;
}

class									ui::symbol : public engine::texture
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


