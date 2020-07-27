#include "texture_atlas.h"

#define STB_IMAGE_IMPLEMENTATION
#include "libraries/stb_image/stb_image.h"

					texture_atlas::texture_atlas(const path &source)
{
	unsigned char 	*data;
	int				number_of_components;
	int				width;
	int				height;

	glGenTextures(1, &value);
	stbi_set_flip_vertically_on_load(1);

	data = stbi_load(source.c_str(), &width, &height, &number_of_components, 0);
	assert(data != nullptr and "Can't create texture_atlas");

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

	texture_atlas::use(true);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(data);

	assert(width % texture_size_in_pixels[0] == 0 and "Can't index texture atlas");
	assert(height % texture_size_in_pixels[1] == 0 and "Can't index texture atlas");

	number_of_textures.x = width / texture_size_in_pixels[0];
	number_of_textures.y = height / texture_size_in_pixels[0];

	texture_size.x = 1.f / (float)number_of_textures.x;
	texture_size.y = 1.f / (float)number_of_textures.y;
}

					texture_atlas::~texture_atlas()
{
	glDeleteTextures(1, &value);
}

void 				texture_atlas::associate_texture_with_block(block::type type, ivec2 index)
{
	instance()->associations[type] = index;
}

vec2				texture_atlas::get_texture_size()
{
	return (instance()->texture_size);
}

vec2				texture_atlas::get_texture_position(block::type type)
{
	auto			texture_size = instance()->texture_size;
	auto			iterator = instance()->associations.find(type);

	assert(iterator != instance()->associations.end() and "There is no texture for this type of block");
	return {iterator->second.x * texture_size.x, iterator->second.y * texture_size.y};
}

void				texture_atlas::use(bool state)
{
	glBindTexture(GL_TEXTURE_2D, state ? value : 0);
}