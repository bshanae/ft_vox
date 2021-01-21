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

void 				texture::bind(bool state) const
{
	glBindTexture(GL_TEXTURE_2D, state ? value : 0);
}