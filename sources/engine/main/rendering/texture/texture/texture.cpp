#include "texture.h"

using namespace		engine;

					texture::texture()
{
	glGenTextures(1, &_value);
}

					texture::~texture()
{
	glDeleteTextures(1, &_value);
}


GLuint				texture::get_width() const
{
	return _width;
}

GLuint				texture::get_height() const
{
	return _height;
}

void 				texture::use(bool state)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, state ? _value : 0);
}