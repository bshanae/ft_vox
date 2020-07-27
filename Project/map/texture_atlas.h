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

	static
	void 				associate_texture_with_block(block::type type, ivec2 index);

	[[nodiscard]]
	static vec2			get_texture_size();
	[[nodiscard]]
	static vec2			get_texture_position(block::type type);

private :

	static
	inline
	constexpr int		texture_size_in_pixels[2] = {48, 48};

	ivec2 				number_of_textures = ivec2(0);
	vec2 				texture_size = vec2(0);

	GLuint				value = -1;

	using 				associations_type = std::map<block::type, ivec2>;
	associations_type	associations;

	void				use(bool state);
};