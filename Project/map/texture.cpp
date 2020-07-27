#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "libraries/stb_image/stb_image.h"

					texture::texture(const path &source)
{
	unsigned char 	*data;
	int				number_of_components;
	int				width;
	int				height;

	glGenTextures(1, &value);
	stbi_set_flip_vertically_on_load(1);

	data = stbi_load(source.c_str(), &width, &height, &number_of_components, 0);
	assert(data != nullptr and "Can't create texture");

	GLenum			format = 0;

	switch (number_of_components)
	{
		case 1 :
			format = GL_RED;
			break ;

		case 3 :
			format = GL_RGB;
			break ;

		case 4 :
			format = GL_RGBA;
			break ;

		default :
			assert(false and "Unknown texture format");

	}

	texture::use(true);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture::use(false);

	stbi_image_free(data);
}

					texture::~texture()
{
	glDeleteTextures(1, &value);
}

void				texture::use(bool state)
{
	glBindTexture(GL_TEXTURE_2D, state ? value : 0);
}