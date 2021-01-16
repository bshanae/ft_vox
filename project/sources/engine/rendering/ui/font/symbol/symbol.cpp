#include "symbol.h"

#include "engine/rendering/ui/font/symbol/symbol_renderer.h"

using namespace		ui;

					symbol::symbol(FT_Face &face)
{
	size = ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
	bearing = ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
	advance = (int)((unsigned int)face->glyph->advance.x >> 6u);

	texture::bind(true);

	glTexImage2D
	(
		GL_TEXTURE_2D, 0, GL_RED,
		face->glyph->bitmap.width, face->glyph->bitmap.rows,
		0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture::bind(false);
}

ivec2				symbol::get_size() const
{
	return size;
}

ivec2				symbol::get_bearing() const
{
	return bearing;
}

int					symbol::get_advance() const
{
	return advance;
}


void 				symbol::render(const ivec2 &position) const
{
	symbol_renderer::render(*this, position);
}