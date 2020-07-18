#pragma once

#include "program/shader.h"
#include "program/uniform.h"

class					program
{
public :
						program(const path &vertex_source, const path &fragment_source);
						~program();

	void				use(bool state)
	{
		glUseProgram(state ? value : 0);
	}

	template			<typename type>
	[[nodiscard]] auto	make_uniform(const std::string &name)
	{
		return (uniform<type>(glGetUniformLocation(value, name.c_str())));
	}

private :

	GLuint 				value;
};
