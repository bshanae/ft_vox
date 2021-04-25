#version 330 core

out vec4			out_color;
in vec3				texture_coordinates;

uniform samplerCube	uniform_cubemap;

void				main()
{
	out_color = texture(uniform_cubemap, texture_coordinates);
}