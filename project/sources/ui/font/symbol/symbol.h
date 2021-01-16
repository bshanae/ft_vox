#pragma once

#include "common/imports/opengl.h"
#include "common/imports/glm.h"
#include "common/imports/freetype.h"
#include "common/imports/std.h"
#include "engine/model/texture/texture.h"

namespace				ui
{
	class				font;

	class				symbol;
}

class					ui::symbol : public engine::texture
{
	friend class		font;

public :

	explicit			symbol(FT_Face &face);
						~symbol() = default;

	ivec2				get_size() const;
	ivec2				get_bearing() const;
	int					get_advance() const;

	void 				render(const ivec2 &position) const;

private :

	ivec2				size;
	ivec2				bearing;
	int					advance;

	shared_ptr<font>	font;
};


