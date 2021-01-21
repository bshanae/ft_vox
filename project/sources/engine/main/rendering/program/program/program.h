#pragma once

#include "engine/main/rendering/program/shader/shader.h"
#include "engine/main/rendering/program/uniform/uniform.h"

namespace			engine
{
	class			program;
}

class				engine::program
{
public :
					program(const path &vertex_source, const path &fragment_source);
					~program();

	void			bind(bool state);

	template		<typename type>
	auto			create_uniform(const string &name)
	{
		return (uniform<type>(glGetUniformLocation(value, name.c_str())));
	}

private :

	GLuint 			value;
};
