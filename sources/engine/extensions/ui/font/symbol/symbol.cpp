#include "symbol.h"

#include "engine/extensions/ui/font/symbol/symbol_renderer.h"

using namespace				engine::ui;

							symbol::symbol(FT_Face &face)
{
	size = ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
	bearing = ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
	advance = (int)((unsigned int)face->glyph->advance.x >> 6u);

	if (face->glyph->bitmap.buffer != nullptr)
		texture = extract_free_type_bitmap(face->glyph->bitmap);
}

ivec2						symbol::get_size() const
{
	return size;
}

ivec2						symbol::get_bearing() const
{
	return bearing;
}

int							symbol::get_advance() const
{
	return advance;
}

bool 						symbol::has_texture() const
{
	return texture != nullptr;
}

void						symbol::use_texture(bool state)
{
	debug::check_critical(texture != nullptr, "[Symbol] Texture is not present");
	texture->use(state);
}

void 						symbol::render(const ivec2 &position)
{
	symbol_renderer::render(*this, position);
}

unique_ptr<engine::texture>	symbol::extract_free_type_bitmap(const FT_Bitmap &bitmap)
{
	auto					texture = make_unique<engine::texture>();

	texture->use(true);

	glTexImage2D
	(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		bitmap.width,
		bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		bitmap.buffer
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture->use(false);

	return texture;
}