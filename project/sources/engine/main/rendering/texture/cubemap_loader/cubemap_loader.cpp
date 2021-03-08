#include "cubemap_loader.h"

#include "engine/main/rendering/texture/cubemap/cubemap.h"

#include "application/common/imports/stb.h"

using namespace				engine;

shared_ptr<cubemap>			cubemap_loader::load
							(
								const string &source_right,
								const string &source_left,
								const string &source_top,
								const string &source_bottom,
								const string &source_front,
								const string &source_back
							)
{
	const vector<string>	sources = {source_right, source_left, source_top, source_bottom, source_front, source_back};

	shared_ptr<cubemap>		cubemap;
	int						width;
	int						height;
	int						number_of_channels;
	unsigned char			*data;

	cubemap = make_shared<engine::cubemap>();
	cubemap->use(true);

	for (GLuint i = 0; i < sources.size(); i++)
	{
		data = stbi_load(sources[i].c_str(), &width, &height, &number_of_channels, 0);

		glTexImage2D
		(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
		);

		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	cubemap->use(false);
	return cubemap;
}