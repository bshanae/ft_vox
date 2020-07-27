#version 400 core

in vec2     		pass_texture_coordinates;

out vec4			color;

uniform sampler2D	uniform_texture;

void		main()
{
	color = texture(uniform_texture, pass_texture_coordinates);
}