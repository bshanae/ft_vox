#pragma once

#include "common/OpenGL.h"
#include "common/global.h"
#include "common/aliases.h"
#include "map/block.h"

class					texture_atlas : public global<texture_atlas>
{
public :

	explicit			texture_atlas(const path &source);
						~texture_atlas() override;

	struct				association
	{
						association(block::type type);

		void			operator = (const ivec2 &value);

		ivec2 			left;
		ivec2 			right;
		ivec2 			top;
		ivec2 			bottom;
		ivec2 			back;
		ivec2 			front;

	private :

		block::type		type;
	};

	static association	&association_for(block::type type);

	static vec2 		texture_size();

private :

	static
	inline
	constexpr int		texture_size_in_pixels[2] = {48, 48};

	ivec2 				number_of_textures = ivec2(0);

	GLuint				value = -1;

	using 				associations_type = std::map<block::type, association>;
	associations_type	associations;
};