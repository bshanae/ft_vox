#pragma once

#include "application/common/imports/opengl.h"

namespace			engine
{
	class 			cubemap;
}

class				engine::cubemap
{
public :
					cubemap();
					~cubemap();

	cubemap			&operator = (const cubemap &other) = default;

	GLuint			get_value() const;

	void 			bind(bool state);

private :

	GLuint			value;
};