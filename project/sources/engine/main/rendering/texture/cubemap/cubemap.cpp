#include "cubemap.h"

using namespace 	engine;

					cubemap::cubemap()
{
	glGenTextures(1, &value);
}

					cubemap::~cubemap()
{
	glDeleteTextures(1, &value);
}

GLuint				cubemap::get_value() const
{
	return value;
}

void 				cubemap::bind(bool state)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, state ? value : 0);
}