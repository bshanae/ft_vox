#pragma once

#include "application/common/debug/debug.h"
#include "application/common/imports/opengl.h"
#include "application/common/imports/glm.h"
#include "application/common/imports/std.h"

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
		debug::check(value != -1u, "[engine::uniform] Uniform is not found");

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
			debug::raise_error("[engine::uniform] Unknown uniform type");
	}

private :

	explicit		uniform(GLuint value) : value(value) {}

	GLuint 			value;
};