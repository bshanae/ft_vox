#include "texture.h"

using namespace		engine;

					texture::texture()
{
	glGenTextures(1, &value);
}

					texture::~texture()
{
	glDeleteTextures(1, &value);
}

GLuint				texture::get_value() const
{
	return value;
}

GLuint				texture::get_width() const
{
	return width;
}

GLuint				texture::get_height() const
{
	return height;
}

void 				texture::bind(bool state)
{
	glBindTexture(GL_TEXTURE_2D, state ? value : 0);
}