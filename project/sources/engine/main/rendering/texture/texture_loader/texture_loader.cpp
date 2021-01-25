#include "texture_loader.h"

#include "application/common/debug/debug.h"

#define STB_IMAGE_IMPLEMENTATION
#include "application/common/imports/stb.h"

using namespace 		engine;

shared_ptr<texture>		texture_loader::load(const path &source)
{
	shared_ptr<texture>	texture;
	unsigned char		*data;
	int					number_of_components;
	int					width;
	int					height;
	GLenum				format;

	stbi_set_flip_vertically_on_load(1);

	texture = make_shared<engine::texture>();

	data = stbi_load(source.c_str(), &width, &height, &number_of_components, 0);
	debug::check_critical(data != nullptr, "[engine::texture_loader] Can't create texture_atlas");

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
			debug::raise_error("[engine::texture_loader] Unknown texture format");
			return nullptr;

	}

	texture->bind(true);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(data);
	texture->bind(false);

	texture->width = width;
	texture->height = height;

	return texture;
}