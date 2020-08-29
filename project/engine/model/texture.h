#pragma once

#include "common/opengl.h"
#include "common/property.h"

class 										texture
{
public :

	property<read_only, GLuint, texture>	value;

											texture()
	{
		GLuint								temporary;

		glGenTextures(1, &temporary);
		value = temporary;
	}
											~texture()
	{
		glDeleteTextures(1, &*value);
	}

	void 									bind(bool state) const
	{
		glBindTexture(GL_TEXTURE_2D, state ? value : 0);
	}
};