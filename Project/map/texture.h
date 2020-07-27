#pragma once

#include "common/OpenGL.h"
#include "common/aliases.h"

class				texture
{
public :

	explicit		texture(const path &source);
					~texture();

	void			use(bool state);

private :

	GLuint			value = -1;
};