#pragma once

#include "world/renderer/shader.h"
#include "world/renderer/uniform.h"

class					program
{
public :
						program(const path &vertex_source, const path &fragment_source);
						~program();

	void				bind(bool state)
	{
		glUseProgram(state ? value : 0);
	}

	template			<typename type>
	[[nodiscard]] auto	create_uniform(const std::string &name)
	{
		return (uniform<type>(glGetUniformLocation(value, name.c_str())));
	}

private :

	GLuint 				value;
};
