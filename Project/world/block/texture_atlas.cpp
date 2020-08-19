#include "texture_atlas.h"

#define STB_IMAGE_IMPLEMENTATION
#include "libraries/stb_image/stb_image.h"

							texture_atlas::texture_atlas(const path &source)
{
	unsigned char			*data;
	int						number_of_components;
	int						width;
	int						height;

	glGenTextures(1, &value);
	stbi_set_flip_vertically_on_load(1);

	data = stbi_load(source.c_str(), &width, &height, &number_of_components, 0);
	assert(data != nullptr and "Can't create texture_atlas");

	GLenum					format = 0;

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

	glBindTexture(GL_TEXTURE_2D, value);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(data);

	assert(width % texture_size_in_pixels[0] == 0 and "Can't index texture atlas");
	assert(height % texture_size_in_pixels[1] == 0 and "Can't index texture atlas");

	number_of_textures.x = width / texture_size_in_pixels[0];
	number_of_textures.y = height / texture_size_in_pixels[1];
}

							texture_atlas::~texture_atlas()
{
	glDeleteTextures(1, &value);
}

							texture_atlas::association::association(enum block::type type) : type(type)
{}

texture_atlas::association	&texture_atlas::association::operator = (const ivec2 &value)
{
	left = value;
	right = value;
	top = value;
	bottom = value;
	back = value;
	front = value;

	return (*this);
}

texture_atlas::association	&texture_atlas::association_for(enum block::type type)
{
	auto 					instance = texture_atlas::instance();
	auto 					iterator = instance->associations.find(type);

	if (iterator == instance->associations.end())
		instance->associations.emplace(type, type);
	return (instance->associations.at(type));
}

vec2						texture_atlas::texture_size()
{
	return {1.f / (float)instance()->number_of_textures.x, 1.f / (float)instance()->number_of_textures.y};
}