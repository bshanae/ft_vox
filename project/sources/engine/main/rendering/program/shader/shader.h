#pragma once

#include "application/common/imports/opengl.h"
#include "application/common/imports/std.h"

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

	static void		write_file_to_stream(stringstream &stream, const path &path);
	void			log_error(const string &shader_string) const;
};
