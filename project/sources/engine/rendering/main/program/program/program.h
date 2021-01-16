#pragma once

#include "engine/rendering/main/program/shader/shader.h"
#include "engine/rendering/main/program/uniform/uniform.h"

namespace				engine
{
	class				program;
}

class					engine::program
{
public :
						program(const path &vertex_source, const path &fragment_source);
						~program();

	void				bind(bool state)
	{
		glUseProgram(state ? value : 0);
	}

	template			<typename type>
	auto				create_uniform(const std::string &name)
	{
		return (uniform<type>(glGetUniformLocation(value, name.c_str())));
	}

private :

	GLuint 				value;
};
