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
					program(const string &vertex_source, const string &fragment_source);
					~program();

	void			use(bool state);

	template		<typename type>
	auto			create_uniform(const string &name)
	{
		auto 		new_uniform = uniform<type>(glGetUniformLocation(value, name.c_str()));

		debug::check(new_uniform.is_valid(), "[program] Uniform for name '" + name + "' is invalid");
		return new_uniform;
	}

private :

	GLuint 			value;

	void			log_error() const;
};
