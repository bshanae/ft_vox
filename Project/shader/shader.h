#pragma once

#include "libraries/glad/include/glad/glad.h"

#include <filesystem>

class				shader
{
	friend class	program;

	enum class		type : GLuint
	{
		vertex = GL_VERTEX_SHADER,
		fragment = GL_FRAGMENT_SHADER
	};
					shader(type type, const std::filesystem::path &source);
					~shader();
private :

	GLuint			value;
};
