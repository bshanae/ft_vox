#pragma once

#include "application/common/imports/opengl.h"

namespace			engine
{
	class			texture;
}

class 				engine::texture
{
	friend class	texture_loader;

public :
					texture();
					~texture();

	texture			&operator = (const texture &other) = default;

	GLuint			get_value() const;
	GLuint			get_width() const;
	GLuint			get_height() const;

	void 			bind(bool state);

private :

	GLuint			value;
	int 			width;
	int 			height;
};