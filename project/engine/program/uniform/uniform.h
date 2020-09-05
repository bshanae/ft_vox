#pragma once

#include "common/opengl.h"
#include "common/glm.h"
#include "common/aliases.h"

namespace			engine
{
	class			program;

	template		<typename>
	class			uniform;
}

template 			<typename type>
class 				engine::uniform
{
	friend class	program;

public :
					uniform() = default;
					~uniform() = default;

	void			upload(const type &data) const
	{
		assert(value != -1u and "Bad uniform");
		if constexpr (is_same<type, int>::value)
			glUniform1i(value, data);
		else if constexpr (is_same<type, float>::value)
			glUniform1f(value, data);
		else if constexpr (is_same<type, vec3>::value)
			glUniform3f(value, data.x, data.y, data.z);
		else if constexpr (is_same<type, vec4>::value)
			glUniform4f(value, data.x, data.y, data.z, data.w);
		else if constexpr (is_same<type, mat4>::value)
			glUniformMatrix4fv(value, 1, GL_FALSE, value_ptr(data));
		else
			assert(false and "Unexpected uniform type");
	}

private :

	explicit		uniform(GLuint value) : value(value)
					{}

	GLuint 			value;
};