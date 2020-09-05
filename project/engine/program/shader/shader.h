#pragma once

#include "common/opengl.h"
#include "common/aliases.h"

namespace			engine
{
	class			program;

	class			shader;
};

class				engine::shader
{
	friend class	engine::program;

	enum			type : GLuint
	{
		vertex = GL_VERTEX_SHADER,
		fragment = GL_FRAGMENT_SHADER
	};
					shader(type type, const path &source);
					~shader();
private :

	GLuint			value;
};
