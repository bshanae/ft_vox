#version 400 core

in vec2     		pass_texture_coordinates;

out vec4			out_color;

uniform sampler2D	uniform_texture;

void				main()
{
	vec4			sampled;

	sampled = vec4(1, 1, 1, texture(uniform_texture, pass_texture_coordinates).r);
	out_color = vec4(0, 0, 0, 1) * sampled;
}