#pragma once

#include "engine/namespace.h"

#include "engine/abstract/OpenGL_wrapper.h"

template 			<typename type>
class 				engine::program::uniform : public engine::abstract::OpenGL_wrapper
{
	friend class	engine::program::program;

public :
					uniform() = default;
					~uniform() override = default;

	void			upload(const type &data) const
	{
		if (object == -1)
			error::raise(error::id::uniform_bad_value);
		if constexpr (std::is_same<type, int>::value)
			glUniform1i(object, data);
		else if constexpr (std::is_same<type, float>::value)
			glUniform1f(object, data);
		else if constexpr (std::is_same<type, glm::vec3>::value)
			glUniform3f(object, data.x, data.y, data.z);
		else if constexpr (std::is_same<type, glm::vec4>::value)
			glUniform4f(object, data.x, data.y, data.z, data.w);
		else if constexpr (std::is_same<type, glm::mat4>::value)
			glUniformMatrix4fv(object, 1, GL_FALSE, value_ptr(data));
		else
			error::raise(error::id::uniform_bad_type);
	}

private :

	explicit		uniform(GLuint value)
	{
		object = value;
	}
};