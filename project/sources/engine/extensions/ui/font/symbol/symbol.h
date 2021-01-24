#pragma once

#include "engine/main/rendering/texture/texture/texture.h"

#include "application/common/imports/opengl.h"
#include "application/common/imports/glm.h"
#include "application/common/imports/freetype.h"
#include "application/common/imports/std.h"

namespace				engine::ui
{
	class				font;
	class				symbol;
}

class					engine::ui::symbol : public engine::texture
{
	friend class		font;

public :

	explicit			symbol(FT_Face &face);
						~symbol() = default;

	ivec2				get_size() const;
	ivec2				get_bearing() const;
	int					get_advance() const;

	void 				render(const ivec2 &position);

private :

	ivec2				size;
	ivec2				bearing;
	int					advance;

	shared_ptr<font>	font;
};