#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"

class				shader
{
	friend class	program;

	enum class		type : GLuint
	{
		vertex = GL_VERTEX_SHADER,
		fragment = GL_FRAGMENT_SHADER
	};
					shader(type type, const path &source);
					~shader();
private :

	GLuint			value;
};
