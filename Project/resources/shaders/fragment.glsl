#version 400 core

in vec2     		pass_texture_coordinates;
in float			pass_light_level;

out vec4			out_color;

uniform sampler2D	uniform_texture;

void		main()
{
	vec4	temp_color;

	temp_color = texture(uniform_texture, pass_texture_coordinates);
	temp_color.xyz *= pass_light_level;

	out_color = temp_color;
}