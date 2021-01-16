#pragma once

#include "common/imports/opengl.h"

namespace			engine
{
	class			texture;
}

class 				engine::texture
{
public :
					texture();
					~texture();

	GLuint			get_value() const;

	void 			bind(bool state) const;

private :

	GLuint			value;
};