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

void 				cubemap::use(bool state)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, state ? value : 0);
}